#include <SDL3/SDL.h>
#include <libpng16/png.h>
#include <psputility.h>
#include <psputility_msgdialog.h>

#include "render.h"
#include "main.h"

int winW = 480;
int winH = 272;

char debugText[512][512];

SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;

int logI = 0;
int debugFilesI = 0;

void onSDLLog(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    strcpy(debugText[logI], message);
    logI++;
}

SDL_EnumerationResult printFiles(void *userdata, const char *dirname, const char *fname)
{
    strcpy(debugText[debugFilesI], fname);
    debugFilesI++;
    return SDL_ENUM_CONTINUE;
}

SDL_FRect createRectFromRenderable(Renderable renderable)
{
    SDL_FRect rect = {renderable.x, renderable.y, renderable.w, renderable.h};
    return rect;
}

void renderRect(Renderable renderable, int r, int g, int b, int a)
{
    SDL_FRect rect = createRectFromRenderable(renderable);
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderFillRect(rend, &rect);
}

void renderTexture(TextureRenderable renderable)
{
    SDL_FRect rect = createRectFromRenderable(renderable.base);
    SDL_RenderTexture(rend, renderable.tex, NULL, &rect);
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

void render()
{
    SDL_RenderClear(rend);

    if (AP_Menu)
        AP_Menu->render();
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    for (int i = 0; i < 512; i++)
    {
        SDL_RenderDebugText(rend, 0, i * 8, debugText[i]);
    }

    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderPresent(rend);
}

void REND_quit()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int REND_init()
{
    SDL_SetLogOutputFunction(onSDLLog, NULL);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Failed to init SDL!");
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("main", winW, winH, 0, &win, &rend))
    {
        SDL_Log("Failed create renderer!");
        return 2;
    }

    //SDL_EnumerateDirectory("assets", printFiles, NULL);

    return 0;
}