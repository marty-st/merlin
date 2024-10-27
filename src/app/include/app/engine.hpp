#ifndef ENGINE_INCLUDE
#define ENGINE_INCLUDE

#include <osi/application.hpp>

#include <memory>

// Forward declaration for friend class functionality.
namespace gui
{

class GUI;

};

using gui_ptr = std::unique_ptr<::gui::GUI>;

namespace app
{

/**
 * Derived from `Application`. This class represents the Merlin Engine implementation.
 */
class Engine : public osi::Application
{
    friend class ::gui::GUI;
    // Data used to render the GUI
    gui_ptr gui = nullptr;

    /**
     * @copydoc ::osi::Application::update()
     */
    void update() override;

    /**
     * @copydoc ::osi::Application::render()
     */
    void render() override;
public:
    /**
     * @copydoc ::osi::Application::Application()
     */
    Engine(const osi::ApplicationConfig &app_cfg);
    
    ~Engine() = default;
};

} // namespace app

#endif
