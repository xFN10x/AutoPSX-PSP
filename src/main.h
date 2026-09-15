#ifndef MAIN_H
#include <SDL3_mixer/SDL_mixer.h>
#define MAIN_H
typedef struct Menu
{
    char* name;
    void (*render)();
    void (*init)();
    void (*ready)();
} Menu;

extern bool AP_Running;
extern Menu* AP_Menu;
extern MIX_Mixer *AP_Mixer;
extern bool AP_CurrentMenuReady;

void setMenu(Menu* men);
#endif