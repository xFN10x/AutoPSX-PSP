#include "render.h"

struct TextureRenderable testTexture;
struct Renderable testRect = {"testt",100,0,100,100};

//Called when loaded
void M_Opening_Init() {
    testTexture = createTextureRenderable("assets/test.png", "test", 0,0);
    SDL_Log("init opening");
    SDL_Log("Texture size %sx%s w%s h%s", testTexture.base.x, testTexture.base.y, testTexture.base.w, testTexture.base.h);


}

void M_Opening_Ready() {

}

//Called each frame
void M_Opening_Render() {
    //renderTexture(testTexture);
    //renderRect(testRect, 255,0,0,255);
}
