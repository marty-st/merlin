#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // Initial window size in pixels
    const int screen_width = 800;
    const int screen_height = 600;
    // Initialize SDL video subsystem (Returns 0 on success)
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        // Error initializing SDL
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Could not initialize SDL2: %s",
                     SDL_GetError());
        return 3;
    }

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

    // Setup SDL Window
    // Description: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    static SDL_Window* window_ptr = SDL_CreateWindow("Merlin Engine", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          screen_width,
                                          screen_height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_ptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Could not create window: %s", 
                     SDL_GetError());
        return 3;
    }

    // Setup OpenGL context
    static SDL_GLContext gl_context_ptr = SDL_GL_CreateContext(window_ptr);
    if (!gl_context_ptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Could not create OpenGL context: %s", 
                     SDL_GetError());
        return 3;
    }

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