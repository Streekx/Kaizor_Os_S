#ifndef KAIZOR_SERVER_H
#define KAIZOR_SERVER_H

#include <wayland-server-core.h>

#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/render/allocator.h>

#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_scene.h>

#include <wlr/types/wlr_xdg_shell.h>

struct kaizor_server {
    struct wl_display *display;
    struct wlr_backend *backend;

    struct wlr_renderer *renderer;
    struct wlr_allocator *allocator;

    struct wlr_output_layout *output_layout;

    struct wlr_scene *scene;
    struct wlr_scene_output_layout *scene_layout;

    struct wlr_xdg_shell *xdg_shell;

    struct wl_list outputs;
    struct wl_list views;

    struct wl_listener new_output;
    struct wl_listener new_xdg_surface;
};

void kaizor_server_init(struct kaizor_server *server);
void kaizor_server_run(struct kaizor_server *server);

#endif
