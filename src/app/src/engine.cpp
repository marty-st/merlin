#include <app/engine.hpp>

#include <osi/opengl.hpp>

namespace app
{

Engine::Engine(const osi::ApplicationConfig &app_cfg) 
: Application(app_cfg) {}

void Engine::update()
{

}

void Engine::render()
{
    glViewport(0, 0, window().size().x, window().size().y);
    assert(glGetError() == GL_NO_ERROR);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    assert(glGetError() == GL_NO_ERROR);
    glClear(GL_COLOR_BUFFER_BIT);
    assert(glGetError() == GL_NO_ERROR);
}

} // namespace app