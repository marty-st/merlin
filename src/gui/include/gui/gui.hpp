#ifndef GUI_GUI
#define GUI_GUI

#include <app/engine.hpp>
#include <util/math.hpp>

namespace gui
{

/**
 * Manager class for rendering the GUI. Has access to private members of `Engine`.
 */
class GUI
{
    // Pointer to the `Engine` instance
    ::app::Engine* engine_ptr = nullptr;

    /**
     * Updates attributes of the GUI class each rendered frame, 
     * before the `render()` method is called.
     */
    void update();

    /**
     * Displays Frames-Per-Second counter on screen. Frequency of the updates
     * can be adjusted by changing the `fps_interval` attribute.
     */
    void fps();

    /**
     * Displays currently held down keyboard keys and mouse buttons.
     */
    void input();

public:
    // If `false`, the `render()` function is skipped 
    bool show_gui = true;

    // Last FPS value shown on screen
    float last_fps = 0;
    // Interval (in seconds) of calculating a new FPS value 
    double fps_interval = 0.2;
    // Time stamp (in seconds) of the last FPS calculation
    double last_fps_time = 0;

    // Window size
    glm::u32vec2 w_size;

    /**
     * @param _engine_ptr Pointer to the associated `Engine` instance
     */
    GUI(::app::Engine* _engine_ptr);

    /**
     * @return Pointer to the associated `Engine` instance
     */
    ::app::Engine* const engine() const;

    /**
     * Calls all the rendering functions of the GUI manager.
     */
    void render();

};

}

#endif // GUI_GUI
