#include <SDL3/SDL.h>
#include <string.h>

const char *GD_GameIdsJson;

void loadIds() {
    size_t size = 0;
    char* buf = (char*)SDL_LoadFile("assets/games.json", &size);
    if (buf == NULL) {
        SDL_Log("Failed to load game ids: %s", SDL_GetError());
    }

    SDL_Log("Loaded: %d bytes", size);
    

    GD_GameIdsJson = buf;
}