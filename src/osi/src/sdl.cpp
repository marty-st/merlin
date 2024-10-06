#include <SDL2/SDL.h>
#include <osi/sdl.hpp>

#include <string>

void SDL_error(const char* message)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                 (std::string(message) + std::string(": %s")).c_str(),
                 SDL_GetError());
}

bool init_SDL(uint8_t option)
{
    // Returns 0 on success
    if (SDL_Init(option))
    {
        SDL_error("Could not initialize SDL2");
        return false;
    }
    
    return true;
}

void setup_SDL_GL_attributes()
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_GLattr
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

SDL_Window* setup_SDL_window(const int screen_width, const int screen_height)
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    SDL_Window* window_ptr = SDL_CreateWindow("Merlin Engine", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          screen_width,
                                          screen_height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_ptr)
    {
        SDL_error("Could not create window: %s");
        return nullptr;
    }

    return window_ptr;
}

SDL_GLContext setup_SDL_GL_context(SDL_Window* window_ptr)
{
    SDL_GLContext gl_context_ptr = SDL_GL_CreateContext(window_ptr);
    if (!gl_context_ptr)
    {
        SDL_error("Could not create OpenGL context: %s"); 
        return nullptr;
    }

    return gl_context_ptr;
}