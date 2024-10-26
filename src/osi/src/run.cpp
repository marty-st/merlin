#include <osi/run.hpp>

#include <app/engine.hpp>
#include <osi/application.hpp>
#include <osi/imgui.hpp>
#include <osi/opengl.hpp>
#include <osi/sdl.hpp>
#include <osi/timer.hpp>

#include <cassert>
#include <functional>
#include <memory>
#include <stdexcept>

namespace osi
{

// Modify this config in the header file
static ApplicationConfig app_cfg;
// Pointer of the Application in the run loop
static std::unique_ptr<Application> application_ptr = nullptr;

// static function does not have external linkage, which means other compilation units 
// (i.e. object files) cannot link to it, because it's not in the symbol table.
// which is why, these are not static, cause they are called in main.cpp
// can be changed tho, if main.cpp calls a different function altogether.

void start()
{   
    SDL_start(sdl_cfg);

    // Setup glad function pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Error: The call to 'gladLoadGLLoader' has FAILED.");

    IMGUI_start();
}

void run()
{
    start();

    // Modify this to select which type of Application is initialized
    app_cfg.constructor = []() { return std::make_unique<app::Engine>(app_cfg); };

    try
    {
        application_ptr = app_cfg.constructor();
    }
    catch (...)
    {
        finish();
        throw;
    }

    if (application_ptr == nullptr)
    {
        finish();
        throw std::logic_error("Error: Construction of the application has FAILED.");
    }

    // NOTE: If these weren't static in sdl.hpp, they would only have to exist once
    //       -> no need for link_pointers_to_SDL() function
    Keyboard* const keyboard = &application_ptr->app_keyboard;
    Mouse* const mouse = &application_ptr->app_mouse;
    Timer* const timer = &application_ptr->app_timer;
    Window* const window = &application_ptr->app_window;

    link_pointers_to_SDL(keyboard, mouse, window);

    bool running = true;
    timer->initialize();

    while (running)
    {
        SDL_run(running);

        timer->updateBeforeFrame();

        // start frame
        IMGUI_new_frame();

        // app update, render
        glViewport(0, 0, window->size().x, window->size().y);
        assert(glGetError() == GL_NO_ERROR);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        assert(glGetError() == GL_NO_ERROR);
        glClear(GL_COLOR_BUFFER_BIT);
        assert(glGetError() == GL_NO_ERROR);

        // finish frame
        window->resetAfterFrame();
        keyboard->resetAfterFrame();
        mouse->resetAfterFrame();
        timer->updateAfterFrame();

        IMGUI_render();

        SDL_swap_buffer();
    }

    finish();
}

void finish()
{
    IMGUI_finish();
    SDL_finish();
}

} // namespace osi
