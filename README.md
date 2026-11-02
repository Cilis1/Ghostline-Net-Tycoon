# Ghostline: Net Tycoon

A native, windowed cyberpunk tycoon game written in C++17 with SDL2. It is not a browser game. The Windows release includes `Ghostline-Installer.exe`: run it and it downloads the latest Windows game bundle from this repository's GitHub Releases, installs it under your user profile, and launches the game. No administrator access is required. An internet connection is needed for installation.

## Windows quick install

1. Download **Ghostline-Installer.exe** from the [latest GitHub release](https://github.com/Cilis1/Ghostline-Net-Tycoon/releases/latest).
2. Run it. The installer fetches `Ghostline-Windows-x64.zip` from the latest release, unpacks the game into `%LOCALAPPDATA%\\Programs\\Ghostline Net Tycoon`, and starts it.

The installer and bundled Windows game are built and attached to each tagged GitHub release by `.github/workflows/windows-release.yml`.

## Build from source

Install a C++17 compiler, CMake 3.16+, and SDL2 development libraries, then:

```sh
cmake -S . -B build
cmake --build build
./build/ghostline
```

On Windows, run `build\\Release\\ghostline.exe` (or the configuration folder used by your generator). See your platform's SDL2 documentation for installation details.

## Play

Click a node to select it, then click the Build/Upgrade button in the site control panel. Press **T** to advance one minute and collect production. Press **Q** or **Escape** to close the game. Routes unlock as your users grow. Trace from risky services can trigger a temporary corporate sweep, but never destroys progress.
