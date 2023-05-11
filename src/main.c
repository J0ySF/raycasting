#include "config.h"

#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PRESENT_WIDTH, PRESENT_HEIGHT, SDL_WINDOW_RESIZABLE);
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

    while(1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    goto Quit;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, 0, PRESENT_WIDTH, PRESENT_HEIGHT);
        SDL_RenderDrawLine(renderer, PRESENT_WIDTH, 0, 0, PRESENT_HEIGHT);
        SDL_RenderPresent(renderer);
    }

    Quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
