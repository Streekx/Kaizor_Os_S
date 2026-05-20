# KaizorOS

KaizorOS is a custom operating system project built from scratch, featuring a modern GUI compositor, system services, and a complete application suite.

## Structure

- `docs/` — Documentation (roadmap, architecture, build guide, GUI design, API reference, ISO release)
- `base/` — Base system configs, patches, and branding
- `kernel/` — Kernel and modules
- `gui/` — GUI components (compositor, shell, panel, launcher, settings, file manager, notifications, greeter, widgets, themes)
- `services/` — System daemons (session, network, bluetooth, power, audio, update)
- `apps/` — Built-in applications (terminal, browser, text editor, calculator, system monitor)
- `assets/` — Wallpapers, icons, fonts, sounds, animations
- `installer/` — CLI and GUI installers, partitioner
- `packaging/` — Package manifest and ports overlay
- `build-system/` — Build scripts, package lists, overlay, and output
- `tests/` — Compositor, GUI, and service tests
- `tools/` — Theme editor, icon builder, debug tools
- `.github/workflows/` — CI/CD pipelines

## Building

See `docs/build-guide.md` for full build instructions.

```sh
cd build-system
./scripts/build_world.sh
./scripts/build_gui.sh
./scripts/build_iso.sh
```

## License

See [LICENSE](LICENSE).
