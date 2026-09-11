#include <pspuser.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <stdbool.h>

#include "render.h"
#include "m_opening.h"

// PSP_MODULE_INFO is required
PSP_MODULE_INFO("AutoPSX", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

typedef struct Menu
{
    char* name;
    void (*render)()
} Menu;

struct Menu opening = {"opening", MRender_opening};


bool running = true;
Menu* menu = &opening;

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}


int main(void)  {
    // Use above functions to make exiting possible
    setup_callbacks();
    
    // Print Hello World! on a debug screen on a loop
    pspDebugScreenInit();
    REND_init();

    while(running) {
        menu->render();
        
        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf(menu->name);
        sceDisplayWaitVblankStart();
    }

    return 0;
}
