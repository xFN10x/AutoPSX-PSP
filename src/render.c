#include <SDL3/SDL.h>
#include <libpng16/png.h>

#include "render.h"
#include "main.h"

int winW = 480;
int winH = 272;

SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;



SDL_FRect createRectFromRenderable(Renderable renderable) {
    SDL_FRect rect = {renderable.x,renderable.y,renderable.w, renderable.h};
    return rect;
}

void renderRect(Renderable renderable, int r, int g, int b, int a) {
    SDL_FRect rect = createRectFromRenderable(renderable);
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderFillRect(rend, &rect);
}

void renderTexture(TextureRenderable renderable)
{
    SDL_FRect rect = createRectFromRenderable(renderable.base);
    SDL_RenderTexture(rend, renderable.tex, &rect, NULL);
}

TextureRenderable createTextureRenderable(char *texPath, char *name,
                                          int x,
                                          int y)
{
    TextureRenderable nil = {};
    SDL_Surface *surf = SDL_LoadSurface(texPath);
    if (surf == NULL)
    {
        SDL_Log("Failed to load: %s\n%s", texPath, SDL_GetError());
        return nil;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_DestroySurface(surf);
    if (tex == NULL)
    {
        SDL_Log("Failed to create: %s\n%s", texPath, SDL_GetError());
        return nil;
    }

    float *w;
    float *h;

    SDL_GetTextureSize(tex, w, h);
    TextureRenderable returning = {name, x, y, *w, *h, tex};
}

void render() {
    SDL_RenderClear(rend);

    AP_Menu->render();

    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderPresent(rend);
}

void REND_quit() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int REND_init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("main", winW, winH, 0, &win, &rend))
    {
        return 2;
    }

    return 0;
}