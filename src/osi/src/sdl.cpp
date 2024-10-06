#include <osi/sdl.hpp>

#include <stdexcept>
#include <string>

namespace osi
{

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

void setup_SDL_window(const int screen_width, const int screen_height)
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    window_ptr = SDL_CreateWindow("Merlin Engine", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          screen_width,
                                          screen_height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_ptr)
    {
        SDL_error("Could not create window: %s");
        throw;
    }
}

void setup_SDL_GL_context()
{
    gl_context_ptr = SDL_GL_CreateContext(window_ptr);
    if (!gl_context_ptr)
    {
        SDL_error("Could not create OpenGL context: %s"); 
        throw;
    }
}

void SDL_start()
{
    setup_SDL_GL_attributes();

    // Initialize SDL video subsystem
    if (!init_SDL(SDL_INIT_VIDEO))
        throw std::runtime_error("Error: Initialisation of the SDL2 library has FAILED.");

    // Setup SDL Window
    setup_SDL_window(screen_width, screen_height);
    if (!window_ptr)
        throw std::runtime_error("Error: The call 'SDL_CreateWindow' function has FAILED.");

    // Setup OpenGL context
    setup_SDL_GL_context();
    if (!gl_context_ptr)
        throw std::runtime_error("Error: The call 'SDL_GL_CreateContext' function has FAILED.");
}

void SDL_run(bool &running)
{
    SDL_Event event;

        // Loop until there are no more pending events to process
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                running = false; // Stop running if the window is closed
        }

        SDL_GL_SwapWindow(window_ptr);
}

void SDL_finish()
{
    if (gl_context_ptr != nullptr)
    {
        SDL_GL_DeleteContext(gl_context_ptr);
        gl_context_ptr = nullptr;
    }

    SDL_DestroyWindow(window_ptr);
    window_ptr = nullptr;

    SDL_Quit();
}

} // namespace osi