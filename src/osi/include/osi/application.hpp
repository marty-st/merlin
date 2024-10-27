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

/**
 * @copydoc ::osi::Config
 * Class inherits from `Config`. Used in the constructor of `Application`-type objects. 
 */
struct ApplicationConfig : public Config
{
    // Defines a constructor for an Application-inheriting class. 
    // Has to be set after `ApplicationConfig` has been initialized.
    std::function<std::unique_ptr<osi::Application>()> constructor;

    ~ApplicationConfig() = default;
};

/**
 * Abstract class (interface) that serves as a bridge between the `osi` and the rest of the project.
 * Holds `osi` structures (`keyboard`, `mouse`, `timer`, `window`). Derived classes can acess these by
 * homonymous methods respectively.
 * 
 * The class needs to be initialized using an `ApplicationConfig` object. (Might not be needed
 * if the config had static variables and methods).
 * 
 * To use a spefic application-type class, derive it from this interface and set the constructor
 * in the run loop to return `std::make_unique<app::YourApplicationClass>(app_cfg)` pointer.
 */
class Application
{
    // friend trick to access attributes directly in the run loop
    friend void ::osi::run();

    // Keyboard owned by the application
    osi::Keyboard app_keyboard;
    // Mouse owned by the application
    osi::Mouse app_mouse;
    // Timer owned by the application
    osi::Timer app_timer;
    // Window owned by the application
    osi::Window app_window;

protected:
    /**
     * @return `const` reference to the keyboard encapsulation class
     */
    osi::Keyboard const& keyboard();

    /**
     * @return `const` reference to the mouse encapsulation class
     */
    osi::Mouse const& mouse();

    /**
     * @return `const` reference to the timer encapsulation class
     */
    osi::Timer const& timer();

    /**
     * @return `const` reference to the window encapsulation class
     */
    osi::Window const& window();

    /**
     * Updates the state of the program each frame. This method is reserved to 
     * reflect changes driven by input, animation, physics, time, etc.
     */
    virtual void update() = 0;

    /**
     * Renders the current state of the programmer-defined scene. This method is reserved
     * to execute all the rendering-related functionality.
     */
    virtual void render() = 0;

public:
    /**
     * Constructor requires an `ApplicationConfig` because the window dimensions
     * need to be set.
     * @param app_cfg Initial configuration of the application
     */
    Application(const ApplicationConfig &app_cfg);

    virtual ~Application() = default;
};

} // namespace osi

#endif