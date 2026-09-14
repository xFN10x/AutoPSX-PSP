#include <stdbool.h>
#include <pspdebug.h>
#include <SDL3/SDL_main.h>

#include "render.h"
#include "m_opening.h"
#include "main.h"

struct Menu opening = {"opening", MRender_opening, MInit};

bool AP_Running = true;
Menu *AP_Menu = NULL;

void setMenu(Menu* men) {
    AP_Menu = men;
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
        SDL_Log("Failed to init SDL");
        return 1;
    }

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
