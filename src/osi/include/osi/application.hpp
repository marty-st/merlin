#ifndef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE

#include <osi/config.hpp>
#include <osi/keyboard.hpp>
#include <osi/mouse.hpp>
#include <osi/timer.hpp>
#include <osi/window.hpp>

#include <functional>
#include <memory>

namespace osi
{

void run();
class Application;

struct ApplicationConfig : public Config
{
    // Defines a constructor for an Application-inheriting class. Can be moved to config if config.hpp exists
    std::function<std::unique_ptr<osi::Application>()> constructor;

    ~ApplicationConfig() = default;
};

class Application
{
    friend void ::osi::run();

    osi::Keyboard app_keyboard;
    osi::Mouse app_mouse;
    osi::Timer app_timer;
    osi::Window app_window;

protected:
    osi::Keyboard const& keyboard();
    osi::Mouse const& mouse();
    osi::Timer const& timer();
    osi::Window const& window();

    virtual void update() = 0;
    virtual void render() = 0;

public:
    Application(const ApplicationConfig &app_cfg);
    virtual ~Application() = default;
};

} // namespace osi

#endif