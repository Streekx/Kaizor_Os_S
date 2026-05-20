cmake_minimum_required(VERSION 3.16)
project(kaizor-compositor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(WLR REQUIRED wlroots)
pkg_check_modules(WAYLAND_SERVER REQUIRED wayland-server)
pkg_check_modules(XKBCOMMON REQUIRED xkbcommon)

add_executable(kaizor-compositor
    src/main.c
    src/server.c
)

target_include_directories(kaizor-compositor PRIVATE
    ${WLR_INCLUDE_DIRS}
    ${WAYLAND_SERVER_INCLUDE_DIRS}
    ${XKBCOMMON_INCLUDE_DIRS}
)

target_link_directories(kaizor-compositor PRIVATE
    ${WLR_LIBRARY_DIRS}
    ${WAYLAND_SERVER_LIBRARY_DIRS}
    ${XKBCOMMON_LIBRARY_DIRS}
)

target_compile_options(kaizor-compositor PRIVATE
    ${WLR_CFLAGS_OTHER}
    ${WAYLAND_SERVER_CFLAGS_OTHER}
    ${XKBCOMMON_CFLAGS_OTHER}
)

target_link_libraries(kaizor-compositor
    ${WLR_LIBRARIES}
    ${WAYLAND_SERVER_LIBRARIES}
    ${XKBCOMMON_LIBRARIES}
)
