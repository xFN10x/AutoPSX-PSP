#include "render.h"

struct TextureRenderable testTexture;
struct Renderable testRect = {"testt",100,0,100,100};

void MInit() {
    testTexture = createTextureRenderable("assets/test.png", "test", 0,0);
    SDL_Log("init opening");
    SDL_Log("Texture size %sx%s w%s h%s", testTexture.base.x, testTexture.base.y, testTexture.base.w, testTexture.base.h);
}

void MRender_opening() {
    renderTexture(testTexture);
    renderRect(testRect, 255,0,0,255);
}
