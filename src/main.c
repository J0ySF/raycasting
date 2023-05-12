#include "config.h"
#include "map.h"

#ifndef EMSCRIPTEN

#include <SDL2/SDL.h>

#else

#include <SDL.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#endif

static SDL_Window *window;
static SDL_Renderer *renderer;

static float position_x, position_y, direction_x = -1, direction_y = 0, plane_x = 0, plane_y = 1.0f;

#ifdef EMSCRIPTEN

EM_BOOL emscripten_canvas_resized_callback(int, const void *, void *) {
    int width, height;
    emscripten_get_canvas_element_size("canvas", &width, &height);
    SDL_SetWindowSize(window, width, height);
    return 1;
}

int loop();

void emscripten_loop(void *) {
    if(!loop()) emscripten_cancel_main_loop();
}

#endif

int loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;
        }
    }

    const float r = -0.01f;

    float old_direction_x = direction_x;
    direction_x = direction_x * cosf(r) - direction_y * sinf(r);
    direction_y = old_direction_x * sinf(r) + direction_y * cosf(r);

    float old_plane_x = plane_x;
    plane_x = plane_x * cosf(r) - plane_y * sinf(r);
    plane_y = old_plane_x * sinf(r) + plane_y * cosf(r);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int x = 0; x < PRESENT_WIDTH; x++) {
        float camera_x = 2 * (float)x / (float)PRESENT_WIDTH - 1;
        float ray_direction_x = direction_x + plane_x * camera_x;
        float ray_direction_y = direction_y + plane_y * camera_x;

        float perspective_distance;
        tile_t tile;
        int side;
        map_cast_ray(position_x, position_y, ray_direction_x, ray_direction_y, &perspective_distance, &tile, &side);

        if (tile == TILE_FLOOR) continue;
        SDL_SetRenderDrawColor(renderer,
                               (tile == TILE_WALL_1) << (7 - side),
                               (tile == TILE_WALL_2) << (7 - side),
                               (tile == TILE_WALL_3) << (7 - side),
                               255);

        int line_height = (int)(PRESENT_HEIGHT / perspective_distance);
        int line_start = -line_height / 2 + PRESENT_HEIGHT / 2;
        if(line_start < 0) line_start = 0;
        int line_end = line_height / 2 + PRESENT_HEIGHT / 2;
        if(line_end >= PRESENT_HEIGHT) line_end = PRESENT_HEIGHT - 1;
        SDL_RenderDrawLine(renderer, x, line_start, x, line_end);
    }

    SDL_RenderPresent(renderer);

    return 1;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PRESENT_WIDTH,
                              PRESENT_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed: %s", SDL_GetError());
        return 1;
    }

    if (SDL_RenderSetLogicalSize(renderer, PRESENT_WIDTH, PRESENT_HEIGHT)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_RenderSetLogicalSize failed: %s", SDL_GetError());
        return 1;
    }

    map_create(&position_x, &position_y);

#ifndef EMSCRIPTEN

    while (loop()) {}

#else

    EmscriptenFullscreenStrategy emscripten_fullscreen_strategy;
    emscripten_fullscreen_strategy.scaleMode =  EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH;
    emscripten_fullscreen_strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF,
    emscripten_fullscreen_strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
    emscripten_fullscreen_strategy.canvasResizedCallback = emscripten_canvas_resized_callback;
    emscripten_enter_soft_fullscreen("canvas", &emscripten_fullscreen_strategy);
    emscripten_set_main_loop_arg(emscripten_loop, NULL, 0, 1);

#endif

    map_destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
