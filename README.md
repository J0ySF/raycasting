# Raycasting

## Dependencies

Language: `C23`

Build system: `cmake`

Libraries: `SDL2`

## Supported platforms

### Linux

Requires `cmake` and the `SDL2` development package to be installed.

+ Build program by running `cmake -B .linux && cmake --build .linux`

+ Run via `.linux/raycasting`

### Flatpak

Requires `cmake`, `flatpak` and `flatpak-builder` to be installed.

+ Install flatpak dependencies by running `flatpak install flathub org.freedesktop.Platform//22.08 org.freedesktop.Sdk//22.08`

+ Build program by running `flatpak-builder --force-clean .flatpak pkg/it.joysf.raycasting.yml`

+ Run via `flatpak-builder --run .flatpak .flatpak/files/manifest.json raycasting`

### Emscripten

Requires `cmake` the `emscripten` toolchain to be installed.

+ Build webpage by running `emcmake cmake -B .emscripten -DCMAKE_BUILD_TYPE=Release && emmake cmake --build .emscripten`

+ Run via `emrun .emscripten/raycasting.html`

## Assets

The font [Px437_IBM_VGA_8x16.ttf](assets%2Ffont%2FPx437_IBM_VGA_8x16.ttf) was created by http://int10h.org/ and is licensed under a Creative Commons
Attribution-ShareAlike 4.0 International License.

## TODO

+ Look at viable compiler optimization flags for all targets.