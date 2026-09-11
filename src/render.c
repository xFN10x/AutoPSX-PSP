#include <SDL3/SDL.h>

int winW = 480;
int winH = 272;

SDL_Window* win = NULL;
SDL_Renderer* rend = NULL;


int REND_init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        return 0;
    }

    if (!SDL_CreateWindowAndRenderer("main", winW, winH, 0, &win, &rend)) {
        return 1;
    }
}
