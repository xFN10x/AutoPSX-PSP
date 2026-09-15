#include <SDL3/SDL.h>
#include <string.h>
#include <yyjson/yyjson.h>

yyjson_doc *GD_GameIdsJson;

char *getGameName(char *id)
{
    return yyjson_get_str(yyjson_obj_get(yyjson_doc_get_root(GD_GameIdsJson), id));
}

void loadIds()
{
    SDL_Log("Reading game ids...");
    size_t size;
    void *buf = SDL_LoadFile("assets/games.json", &size);
    if (buf == NULL)
    {
        SDL_Log("Failed to load game ids: %s", SDL_GetError());
        SDL_free(buf);
        return;
    }

    SDL_Log("Loaded: %zu bytes", size);
    GD_GameIdsJson = yyjson_read(buf, size, 0);
    SDL_Log("Loaded json.");

    SDL_free(buf);

    SDL_Log(getGameName("SLUS-00067"));
}
