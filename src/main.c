#include "config.h"

#ifndef EMSCRIPTEN

#include <SDL2/SDL.h>

#else

#include <SDL.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#endif

static SDL_Window *window;
static SDL_Renderer *renderer;

#ifdef EMSCRIPTEN

EM_BOOL emscripten_canvas_resized_callback(int, const void *, void *) {
    int width, height;
    emscripten_get_canvas_element_size("canvas", &width, &height);
    SDL_SetWindowSize(window, width, height);
    return true;
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 0, PRESENT_WIDTH, PRESENT_HEIGHT);
    SDL_RenderDrawLine(renderer, PRESENT_WIDTH, 0, 0, PRESENT_HEIGHT);
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

#ifndef EMSCRIPTEN

    while (loop()) {}

#else

    EmscriptenFullscreenStrategy strategy;
    strategy.scaleMode =  EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH;
    strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF,
    strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
    strategy.canvasResizedCallback = emscripten_canvas_resized_callback;
    emscripten_enter_soft_fullscreen("canvas", &strategy);
    emscripten_set_main_loop_arg(emscripten_loop, NULL, 0, true);

#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
