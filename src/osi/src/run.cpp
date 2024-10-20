#include <osi/run.hpp>
#include <osi/sdl.hpp>
#include <osi/opengl.hpp>

#include <cassert>
#include <stdexcept>

namespace osi
{

// static function does not have external linkage, which means other compilation units 
// (i.e. object files) cannot link to it, because it's not in the symbol table.
// which is why, these are not static, cause they are called in main.cpp
// can be changed tho, if main.cpp call a different function altogether

void start()
{   
    SDL_start(cfg);

    // Setup glad function pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Error: The call to 'gladLoadGLLoader' has FAILED.");
}

void run()
{
    start();

    bool running = true;
    timer.initialize();

    while (running)
    {
        SDL_run(running);

        timer.updateBeforeFrame();

        glViewport(0, 0, window.size().x, window.size().y);
        assert(glGetError() == GL_NO_ERROR);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        assert(glGetError() == GL_NO_ERROR);
        glClear(GL_COLOR_BUFFER_BIT);
        assert(glGetError() == GL_NO_ERROR);

        window.resetAfterFrame();
        keyboard.resetAfterFrame();
        mouse.resetAfterFrame();
        timer.updateAfterFrame();
    }

    finish();
}

void finish()
{
    SDL_finish();
}

} // namespace osi
