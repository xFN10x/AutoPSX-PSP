#include <stdbool.h>
#include <SDL3/SDL_main.h>

#include "render.h"
#include "m_opening.h"
#include "main.h"

struct Menu opening = {"opening", MRender_opening};

bool AP_Running = true;
Menu *AP_Menu = &opening;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    // Use above functions to make exiting possible
    //setup_callbacks();

    // pspDebugScreenInit();
    // pspDebugInstallStdoutHandler(pspDebugScreenPrintData);

    if (REND_init() != 0)
    {
        SDL_Log("Failed to init SDL");
        return 1;
    }

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
