#include <osi/run.hpp>
#include <osi/sdl.hpp>

#include <glad/glad.h>

#include <stdexcept>
#include <cassert>

namespace osi
{

// static function does not have external linkage, which means other compilation units 
// (i.e. object files) cannot link to it, because it's not in the symbol table.
// which is why, these are not static, cause they are called in main.cpp
// can be changed tho, if main.cpp call a different function altogether

void start()
{    
    SDL_start();

    // Setup glad function pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("Error: The call to 'gladLoadGLLoader' has FAILED.");
}

void run()
{
    bool running = true;
    while (running)
    {
        SDL_run(running);
        glViewport(0, 0, screen_width, screen_height);
        assert(glGetError() == GL_NO_ERROR);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        assert(glGetError() == GL_NO_ERROR);
        glClear(GL_COLOR_BUFFER_BIT);
        assert(glGetError() == GL_NO_ERROR);
    }

    finish();
}

void finish()
{
    SDL_finish();
}

} // namespace osi
