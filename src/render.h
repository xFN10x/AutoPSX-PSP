#ifndef RENDER_H
#define RENDER_H
#include <SDL3/SDL.h>

typedef struct Renderable
{
    char *name;
    int x;
    int y;
    float w;
    float h;
} Renderable;

typedef struct TextureRenderable
{
    Renderable base;
    SDL_Texture *tex;
} TextureRenderable;

int REND_init();
SDL_FRect createRectFromRenderable(Renderable renderable);
void renderTexture(TextureRenderable renderable);
void renderRect(Renderable renderable, int r, int g, int b, int a);
struct TextureRenderable createTextureRenderable(char *texPath, char *name,
                                          int x,
                                          int y);
void render();
void REND_quit();
#endif