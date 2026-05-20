#include "server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <wayland-server-core.h>

#include <wlr/backend.h>
#include <wlr/backend/multi.h>

#include <wlr/render/wlr_renderer.h>
#include <wlr/render/allocator.h>

#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>

#include <wlr/types/wlr_scene.h>

#include <wlr/types/wlr_xdg_shell.h>

#include <wlr/util/log.h>

// -----------------------------
// INTERNAL STRUCTS
// -----------------------------

struct kaizor_output {
    struct wl_list link;
    struct kaizor_server *server;

    struct wlr_output *wlr_output;
    struct wl_listener frame;
    struct wl_listener destroy;
};

struct kaizor_view {
    struct wl_list link;
    struct kaizor_server *server;

    struct wlr_xdg_surface *xdg_surface;

    struct wl_listener map;
    struct wl_listener unmap;
    struct wl_listener destroy;
};

// -----------------------------
// OUTPUT HANDLERS
// -----------------------------

static void kaizor_output_frame(struct wl_listener *listener, void *data) {
    (void)data;

    struct kaizor_output *output =
        wl_container_of(listener, output, frame);

    struct kaizor_server *server = output->server;

    struct wlr_scene_output *scene_output =
        wlr_scene_get_scene_output(server->scene, output->wlr_output);

    if (!scene_output) {
        return;
    }

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    wlr_scene_output_commit(scene_output, &now);
}

static void kaizor_output_destroy(struct wl_listener *listener, void *data) {
    (void)data;

    struct kaizor_output *output =
        wl_container_of(listener, output, destroy);

    wl_list_remove(&output->frame.link);
    wl_list_remove(&output->destroy.link);
    wl_list_remove(&output->link);

    free(output);
}

// -----------------------------
// VIEW HANDLERS
// -----------------------------

static void kaizor_view_map(struct wl_listener *listener, void *data) {
    (void)data;

    struct kaizor_view *view =
        wl_container_of(listener, view, map);

    wlr_log(WLR_INFO, "[Kaizor] View mapped");

    // center the window
    struct wlr_box box;
    wlr_output_layout_get_box(view->server->output_layout, NULL, &box);

    int x = (box.width / 2) - (view->xdg_surface->surface->current.width / 2);
    int y = (box.height / 2) - (view->xdg_surface->surface->current.height / 2);

    wlr_scene_node_set_position(&view->xdg_surface->surface->data->node, x, y);
}

static void kaizor_view_unmap(struct wl_listener *listener, void *data) {
    (void)data;

    struct kaizor_view *view =
        wl_container_of(listener, view, unmap);

    wlr_log(WLR_INFO, "[Kaizor] View unmapped");
}

static void kaizor_view_destroy(struct wl_listener *listener, void *data) {
    (void)data;

    struct kaizor_view *view =
        wl_container_of(listener, view, destroy);

    wl_list_remove(&view->map.link);
    wl_list_remove(&view->unmap.link);
    wl_list_remove(&view->destroy.link);
    wl_list_remove(&view->link);

    free(view);
}

// -----------------------------
// XDG SHELL HANDLER
// -----------------------------

static void kaizor_handle_new_xdg_surface(struct wl_listener *listener, void *data) {
    struct kaizor_server *server =
        wl_container_of(listener, server, new_xdg_surface);

    struct wlr_xdg_surface *xdg_surface = data;

    if (xdg_surface->role != WLR_XDG_SURFACE_ROLE_TOPLEVEL) {
        return;
    }

    struct kaizor_view *view = calloc(1, sizeof(struct kaizor_view));
    view->server = server;
    view->xdg_surface = xdg_surface;

    wl_list_insert(&server->views, &view->link);

    // Create scene node for the surface
    struct wlr_scene_tree *tree = wlr_scene_tree_create(&server->scene->tree.node);

    struct wlr_scene_xdg_surface *scene_xdg_surface =
        wlr_scene_xdg_surface_create(tree, xdg_surface);

    // Store node reference in surface->data
    xdg_surface->surface->data = &scene_xdg_surface->node;

    view->map.notify = kaizor_view_map;
    wl_signal_add(&xdg_surface->events.map, &view->map);

    view->unmap.notify = kaizor_view_unmap;
    wl_signal_add(&xdg_surface->events.unmap, &view->unmap);

    view->destroy.notify = kaizor_view_destroy;
    wl_signal_add(&xdg_surface->events.destroy, &view->destroy);

    wlr_log(WLR_INFO, "[Kaizor] New XDG surface created");
}

// -----------------------------
// OUTPUT DISCOVERY
// -----------------------------

static void kaizor_handle_new_output(struct wl_listener *listener, void *data) {
    struct kaizor_server *server =
        wl_container_of(listener, server, new_output);

    struct wlr_output *wlr_output = data;

    wlr_log(WLR_INFO, "[Kaizor] New output: %s", wlr_output->name);

    // Choose preferred mode
    if (!wl_list_empty(&wlr_output->modes)) {
        struct wlr_output_mode *mode =
            wl_container_of(wlr_output->modes.prev, mode, link);

        wlr_output_set_mode(wlr_output, mode);
    }

    wlr_output_enable(wlr_output, true);

    if (!wlr_output_commit(wlr_output)) {
        wlr_log(WLR_ERROR, "[Kaizor] Failed to commit output");
        return;
    }

    wlr_output_layout_add_auto(server->output_layout, wlr_output);

    struct kaizor_output *output = calloc(1, sizeof(struct kaizor_output));
    output->server = server;
    output->wlr_output = wlr_output;

    wl_list_insert(&server->outputs, &output->link);

    output->frame.notify = kaizor_output_frame;
    wl_signal_add(&wlr_output->events.frame, &output->frame);

    output->destroy.notify = kaizor_output_destroy;
    wl_signal_add(&wlr_output->events.destroy, &output->destroy);

    wlr_scene_output_create(server->scene, wlr_output);
}

// -----------------------------
// SERVER INIT / RUN
// -----------------------------

void kaizor_server_init(struct kaizor_server *server) {
    memset(server, 0, sizeof(*server));

    wlr_log_init(WLR_DEBUG, NULL);

    server->display = wl_display_create();
    if (!server->display) {
        fprintf(stderr, "[Kaizor] Failed to create Wayland display\n");
        exit(1);
    }

    server->backend = wlr_backend_autocreate(server->display, NULL);
    if (!server->backend) {
        fprintf(stderr, "[Kaizor] Failed to create wlroots backend\n");
        exit(1);
    }

    server->renderer = wlr_renderer_autocreate(server->backend);
    if (!server->renderer) {
        fprintf(stderr, "[Kaizor] Failed to create renderer\n");
        exit(1);
    }

    server->allocator = wlr_allocator_autocreate(server->backend, server->renderer);
    if (!server->allocator) {
        fprintf(stderr, "[Kaizor] Failed to create allocator\n");
        exit(1);
    }

    wlr_renderer_init_wl_display(server->renderer, server->display);

    server->output_layout = wlr_output_layout_create();

    wl_list_init(&server->outputs);
    wl_list_init(&server->views);

    server->scene = wlr_scene_create();
    server->scene_layout = wlr_scene_attach_output_layout(server->scene, server->output_layout);

    // Output events
    server->new_output.notify = kaizor_handle_new_output;
    wl_signal_add(&server->backend->events.new_output, &server->new_output);

    // XDG shell (for app windows)
    server->xdg_shell = wlr_xdg_shell_create(server->display, 3);
    server->new_xdg_surface.notify = kaizor_handle_new_xdg_surface;
    wl_signal_add(&server->xdg_shell->events.new_surface, &server->new_xdg_surface);

    wlr_log(WLR_INFO, "[Kaizor] Server initialized");
}

void kaizor_server_run(struct kaizor_server *server) {
    const char *socket = wl_display_add_socket_auto(server->display);
    if (!socket) {
        fprintf(stderr, "[Kaizor] Failed to create Wayland socket\n");
        exit(1);
    }

    setenv("WAYLAND_DISPLAY", socket, 1);

    if (!wlr_backend_start(server->backend)) {
        fprintf(stderr, "[Kaizor] Failed to start backend\n");
        exit(1);
    }

    printf("[Kaizor] Wayland running on WAYLAND_DISPLAY=%s\n", socket);

    wl_display_run(server->display);
    wl_display_destroy(server->display);
}
