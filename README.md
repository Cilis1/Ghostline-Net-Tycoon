# Ghostline: Net Tycoon

A native, windowed cyberpunk tycoon game written in C++17 with SDL2. The game opens as a resizable desktop window—there is no browser version. Its graphics use a small built-in pixel font and SDL drawing primitives, so no external art or font assets are required.

## Build and run

Install a C++17 compiler, CMake 3.16+, and SDL2 development libraries, then:

```sh
cmake -S . -B build
cmake --build build
./build/ghostline
```

On Windows, run `build\\Release\\ghostline.exe` (or the configuration folder used by your generator). SDL2 must be installed and discoverable by CMake. On Debian/Ubuntu, install `libsdl2-dev`; on macOS, install SDL2 with Homebrew; on Windows, SDL2's CMake package or pkg-config must be available.

## Play

Click a node to select it, then click the Build/Upgrade button in the site control panel. Press **T** to advance one minute and collect production. Press **Q** or **Escape** to close the game. Routes unlock as your users grow. Trace from risky services can trigger a temporary corporate sweep, but never destroys progress.

## Game systems

- Credits, users, and corporate Trace.
- Six sites/services, three upgrade levels, relay bonuses, privacy mitigation, and a first-service contract.
- Region route unlocks, corporate warnings, and temporary non-destructive sweeps.
- Neon map visualization with built-in pixel lettering; no web runtime.
