# Raycasting

## Dependencies

Build system: `cmake`.

Libraries: `SDL2`.

## Supported platforms

### Linux

Build program by running `pkg/linux.sh`.

Run via `.linux/raycasting`.

### Flatpak

Requires `flatpak` and `flatpak-builder` to be installed.

Install flatpak dependencies by running `flatpak install flathub org.freedesktop.Platform//22.08 org.freedesktop.Sdk//22.08`.

Build and install program by running `pkg/flatpak.sh`.

Run via `flatpak run it.joysf.raycasting`.

### Emscripten

Planned in the future.

## Assets

The font [Px437_IBM_VGA_8x16.ttf](assets%2Ffont%2FPx437_IBM_VGA_8x16.ttf) was created by http://int10h.org/ and is licensed under a Creative Commons
Attribution-ShareAlike 4.0 International License.