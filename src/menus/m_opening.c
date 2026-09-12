#include "render.h"

TextureRenderable testTexture;
struct Renderable testRect = {"testt",100,0,100,100};

void MInit() {
    testTexture = createTextureRenderable("test.png", "test", 0,0);
}

void MRender_opening() {
    renderTexture(testTexture);
    renderRect(testRect, 255,0,0,255);
}
