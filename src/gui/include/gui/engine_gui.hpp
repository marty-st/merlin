#ifndef GUI_ENGINE_GUI
#define GUI_ENGINE_GUI

#include <app/engine.hpp>
#include <gui/gui.hpp>

namespace gui
{

class EngineGUI : public GUI
{
    // Pointer to the `Engine` instance
    ::app::Engine* engine_ptr = nullptr;

    /**
     * @copydoc ::gui::GUI::update()
     */
    void update() override;

public:
    /**
     * @param _engine_ptr Pointer to the associated `Engine` instance
     */
    EngineGUI(::app::Engine* _engine_ptr);

    /**
     * @return Pointer to the associated `Application`
     */
    ::app::Engine* const engine() const;

    /**
     * @copydoc ::gui::GUI::render()
     */
    void render() override;
};

} // namespace gui

#endif
