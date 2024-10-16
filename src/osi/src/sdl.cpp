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

void setup_SDL_window(SDLConfig &cfg)
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    window_ptr = SDL_CreateWindow(cfg.window_title.c_str(), 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          cfg.window_width,
                                          cfg.window_height,
                                          SDL_WINDOW_OPENGL 
                                          | (cfg.fullscreen 
                                            ? SDL_WINDOW_FULLSCREEN_DESKTOP 
                                            : (cfg.resizable 
                                               ? SDL_WINDOW_RESIZABLE 
                                               : SDL_WINDOW_BORDERLESS)
                                            )
                                 );

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

void SDL_start(SDLConfig &cfg)
{
    setup_SDL_GL_attributes();

    // Initialize SDL video subsystem
    if (!init_SDL(SDL_INIT_VIDEO))
        throw std::runtime_error("Error: Initialisation of the SDL2 library has FAILED.");

    // Setup SDL Window
    setup_SDL_window(cfg);
    if (!window_ptr)
        throw std::runtime_error("Error: The call 'SDL_CreateWindow' function has FAILED.");

    // Setup OpenGL context
    setup_SDL_GL_context();
    if (!gl_context_ptr)
        throw std::runtime_error("Error: The call 'SDL_GL_CreateContext' function has FAILED.");
}

void SDL_window_event(const SDL_WindowEvent &window_event)
{
    switch (window_event.event)
    {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            {
                window.size_vec.x = window_event.data1; 
                window.size_vec.y = window_event.data2;
                window.is_resized = true; 
            }
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            window.is_minimized = true; 
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_RESTORED:
            window.is_minimized = false; 
            break;
        case SDL_WINDOWEVENT_ENTER:
            window.is_mouse_in_window = true; 
            break;
        case SDL_WINDOWEVENT_LEAVE:
            window.is_mouse_in_window = false; 
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            window.has_keyboard_focus = true; 
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            window.has_keyboard_focus = false; 
            break;
        default: break;
    }
}

void SDL_run(bool &running)
{
    SDL_Event event;

        // Loop until there are no more pending events to process
        while (SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false; // Stop running if the window is closed
                case SDL_WINDOWEVENT:
                    SDL_window_event(event.window);
                default:
                    break;
            }
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