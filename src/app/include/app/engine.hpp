#ifndef ENGINE_INCLUDE
#define ENGINE_INCLUDE

#include <osi/application.hpp>

namespace app
{

/**
 * Derived from `Application`. This class represents the Merlin Engine implementation.
 */
class Engine : public osi::Application
{
    /**
     * @copydoc ::osi::Application::update()
     */
    void update() override {}

    /**
     * @copydoc ::osi::Application::render()
     */
    void render() override {}
public:
    /**
     * @copydoc ::osi::Application::Application()
     */
    Engine(const osi::ApplicationConfig &app_cfg);
    
    ~Engine() = default;
};

} // namespace app

#endif