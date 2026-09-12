#ifndef MAIN_H
#define MAIN_H
typedef struct Menu
{
    char* name;
    void (*render)();
    void (*init)();
} Menu;

extern bool AP_Running;
extern Menu* AP_Menu;
#endif