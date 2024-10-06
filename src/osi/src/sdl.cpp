#include <SDL2/SDL.h>
#include <osi/sdl.hpp>

bool init_sdl(uint8_t option)
{
    if (SDL_Init(option))
    {
        // Error initializing SDL
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Could not initialize SDL2: %s",
                     SDL_GetError());
        return false;
    }
    
    return true;
}