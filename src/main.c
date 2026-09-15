#include <stdbool.h>
#include <pspdebug.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "render.h"
#include "m_opening.h"
#include "main.h"

struct Menu opening = {"opening", M_Opening_Render, M_Opening_Init, M_Opening_Ready};

bool AP_Running = true;
Menu *AP_Menu = NULL;
bool AP_CurrentMenuReady = false;
MIX_Mixer *AP_Mixer;

void setMenu(Menu* men) {
    SDL_Log("setting menu: %s", men->name);
    AP_Menu = men;
    AP_CurrentMenuReady = false;
    AP_Menu->init();
    SDL_Log("set menu: %s", men->name);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    pspDebugScreenInit();
    
    SDL_SetLogOutputFunction(onSDLLog, NULL);
    if (REND_init() != 0)
    {
        pspDebugScreenPrintf("Failed to init SDL");
        SDL_Log("Failed to init SDL: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (!MIX_Init()) {
        SDL_Log("Failed to init SDL Audio: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    AP_Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    setMenu(&opening);

    while (AP_Running)
    {

        // pspDebugScreenSetXY(0, 0);
        // pspDebugScreenPrintf(AP_Menu->name);
        // pspDebugScreenSetXY(0, 1);
        // pspDebugScreenSetXY(0, 2);

        // sceDisplayWaitVblankStart();
        render();
    }
    REND_quit();

    return 0;
}
