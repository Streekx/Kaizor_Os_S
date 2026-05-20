# Kaizor OS

Kaizor OS is a modern FreeBSD-based operating system with a custom Wayland compositor and a premium desktop environment inspired by macOS, Windows, and Zorin OS.

## Project Goal
- FreeBSD-based OS
- Custom Wayland compositor (wlroots)
- Modern desktop UI (dock, launcher, settings)
- ISO build system like Zorin OS

## GUI Components (Kaizor Desktop)
- **kaizor-compositor** (Wayland compositor engine)
- **kaizor-panel** (dock/taskbar)
- **kaizor-launcher** (start menu)

## Folder Structure
- `gui/` : compositor + desktop apps
- `services/` : system daemons (wifi, bluetooth, power)
- `build-system/` : scripts for ISO generation
- `assets/` : wallpapers, icons, fonts

## Build GUI (FreeBSD)
Install dependencies:
```sh
pkg install wayland wlroots seatd dbus xkbcommon libinput mesa-libs qt6-base qt6-wayland cmake ninja pkgconf
