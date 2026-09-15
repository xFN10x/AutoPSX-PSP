#include "render.h"
#include "main.h"
#include <SDL3_mixer/SDL_mixer.h>

struct TextureRenderable testTexture;
struct Renderable testRect = {"testt", 100, 0, 100, 100};

struct TextureRenderable openingTexture;
MIX_Track *sfxTrack;
MIX_Audio *openingSfx;

// Called when loaded
void M_Opening_Init()
{
    SDL_Log("init opening");
    testTexture = createTextureRenderable("assets/test.png", "test", 0, 0);
    // SDL_Log("Texture size %sx%s w%s h%s", testTexture.base.x, testTexture.base.y, testTexture.base.w, testTexture.base.h);

    openingTexture = createTextureRenderable("assets/openScreen.png", "openingScreen", 0, 0);
    sfxTrack = MIX_CreateTrack(AP_Mixer);
    openingSfx = MIX_LoadAudio(AP_Mixer, "assets/opening.wav", false);

    REND_ClearColour.r = 0;
    REND_ClearColour.g = 0;
    REND_ClearColour.b = 0;
    REND_ClearColour.a = 255;
}

// Called before the first frame renders
void M_Opening_Ready()
{
    MIX_PlayAudio(AP_Mixer, openingSfx);
    SDL_AddTimer(4000, startLoad, NULL);
}

Uint32 startLoad(void *userdata, SDL_TimerID timerID, Uint32 interval) {
    return 0;
}

Uint8 a = 0;
int aTimer = 0;

// Called each frame
void M_Opening_Render()
{
    renderTexture(openingTexture);
    if (aTimer > 3)
    {
        aTimer = 0;
        if (a < 255)
        {
            SDL_SetTextureAlphaMod(openingTexture.tex, a);
            a++;
        }
    }

    aTimer++;
}
