#include <SDL3/SDL.h>
#include <libpng16/png.h>
#include <pspdebug.h>

#include "render.h"
#include "main.h"

int winW = 480;
int winH = 272;

char debugText[512][512];

SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;

int logI = 0;
int debugFilesI = 0;

struct SDL_Color REND_ClearColour = {0,0,0,255};

void onSDLLog(void *userdata, int category, SDL_LogPriority priority, const char *message)
{
    // strcpy(debugText[logI], message);
    pspDebugScreenPrintf(strcat(message, "\n"));
    printf(message);
    // logI++;
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

void setTextureColour(TextureRenderable renderable, struct SDL_Color clr)
{
    SDL_SetTextureAlphaMod(renderable.tex, clr.a);
    SDL_SetTextureColorMod(renderable.tex, clr.r, clr.g, clr.b);
}

TextureRenderable createTextureRenderable(char *texPath, char *name,
                                          int x,
                                          int y)
{
    SDL_Surface *surf = SDL_LoadSurface(texPath);
    Renderable nilBase = {"error", 0, 0, 100, 100};
    TextureRenderable nil = {nilBase, 0};
    SDL_Log("Image path: %s%s", SDL_GetBasePath(), texPath);
    if (!SDL_GetPathInfo(texPath, NULL))
    {
        SDL_Log("Image doesn't exist!: %s%s", SDL_GetBasePath(), texPath);
        return nil;
    }
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

    float w;
    float h;

    if (!SDL_GetTextureSize(tex, &w, &h))
    {
        SDL_Log("Failed to get size of: %s\n%s", texPath, SDL_GetError());
        return nil;
    }
    struct Renderable baseReturning = {name, x, y, w, h};
    struct TextureRenderable returning = {baseReturning, tex};

    SDL_Log("well, this worked: %s", texPath);
    return returning;
}

void render()
{
    //SDL_Log("REND");
    SDL_SetRenderDrawColor(rend, REND_ClearColour.r, REND_ClearColour.g, REND_ClearColour.b, REND_ClearColour.a);
    SDL_RenderClear(rend);

    if (!AP_Menu == NULL)
    {
        if (!AP_CurrentMenuReady)
        {
            AP_CurrentMenuReady = true;
            AP_Menu->ready();
            SDL_Log("READY MENU");
        }
        AP_Menu->render();
    }
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // for (int i = 0; i < 512; i++)
    //{
    //     SDL_RenderDebugText(rend, 0, i * 8, debugText[i]);
    // }

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
    SDL_Log("test");
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

    // SDL_EnumerateDirectory("assets", printFiles, NULL);

    return 0;
}