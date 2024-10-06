#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

#include <osi/sdl.hpp>

int main(int argc, char* argv[])
{
    // Initial window size in pixels
    const int screen_width = 800;
    const int screen_height = 600;

    // Initialize SDL video subsystem
    if (!init_SDL(SDL_INIT_VIDEO))
        return 3;
    
    setup_SDL_GL_attributes();

    // Setup SDL Window
    static SDL_Window* window_ptr = setup_SDL_window(screen_width, screen_height);
    if (!window_ptr)
        return 3;

    // Setup OpenGL context
    static SDL_GLContext gl_context_ptr = setup_SDL_GL_context(window_ptr);
    if (!gl_context_ptr)
        return 3;

    // Setup glad function pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        return 3;

    bool running = true;
    while (running)
    {
        SDL_Event event;

        // Loop until there are no more pending events to process
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                running = false; // Stop running if the window is closed
        }

        glViewport(0, 0, screen_width, screen_height);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window_ptr);
    }

    SDL_GL_DeleteContext(gl_context_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}