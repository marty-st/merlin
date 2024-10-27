#include <app/engine.hpp>

#include <gui/gui.hpp>
#include <osi/opengl.hpp>
#include <util/assumption.hpp>

namespace app
{

Engine::Engine(const osi::ApplicationConfig &app_cfg) 
: Application(app_cfg), gui{std::make_unique<gui::GUI>(this)}
{

}

void Engine::update()
{

}

void Engine::render()
{
    glViewport(0, 0, window().size().x, window().size().y);
    ASSUME(glGetError() == GL_NO_ERROR);
    if (timer().passedIterations() % 10000 > 5000)
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    else
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    ASSUME(glGetError() == GL_NO_ERROR);
    glClear(GL_COLOR_BUFFER_BIT);
    ASSUME(glGetError() == GL_NO_ERROR);

    gui->render();
}

} // namespace app
