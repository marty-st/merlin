#include <osi/application.hpp>

namespace osi
{

Application::Application(const ApplicationConfig &app_cfg)
: app_window{app_cfg.window_width, app_cfg.window_height} {}

osi::Keyboard const& Application::keyboard()
{
    return app_keyboard;
}

osi::Mouse const& Application::mouse()
{
    return app_mouse;
}

osi::Timer const& Application::timer()
{
    return app_timer;
}

osi::Window const& Application::window()
{
    return app_window;
}

} // namespace osi