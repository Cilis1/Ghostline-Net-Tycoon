# Ghostline: Net Tycoon

A cyberpunk browser prototype and a native C++17 game simulation. Build a neighborhood in the forgotten mesh: connect services, grow your audience, and keep corporate Trace below the sweep threshold.

## Browser game

Open `index.html` directly, or serve this folder with any static web server. Browser progress is saved locally. The interface is responsive and designed for mouse and touch.

## Native C++ game

The native playable game uses standard C++17 and has no third-party dependencies:

```sh
cmake -S . -B build
cmake --build build
./build/ghostline
```

Alternatively: `g++ -std=c++17 -O2 src/ghostline.cpp -o ghostline && ./ghostline`.

Commands: `A` to build or upgrade a service, `T` to wait one minute, and `Q` to quit. Build the first service to complete the community contract. Trace rises from conspicuous services; a sweep interrupts risky services temporarily, never destroying progress.

## Included in v0.1.0

- Six services, three upgrade levels, credits, users, and Trace.
- Relay boosts, privacy mitigation, contracts, route unlocks, and non-destructive corporate sweeps.
- Neon cyberpunk map UI plus a terminal-native C++17 edition.
