#ifndef GUI_GUI
#define GUI_GUI

#include <osi/application.hpp>
#include <osi/gui.hpp>
#include <util/math.hpp>

namespace gui
{

/**
 * Manager class for rendering the GUI. Has access to private members of `Application`.
 */
class GUI
{
    // Pointer to the `Application`
    ::osi::Application* application_ptr = nullptr;

protected:
    /**
     * Updates the value shown by `fps` every `fps_interval` seconds.
     * @param current_time Current second
     * @param dt Time it took to generate previous frame
     */
    float updateFPS(const double &current_time, const float &dt);

    /**
     * Displays Frames-Per-Second counter on screen. Frequency of the updates
     * can be adjusted by changing the `fps_interval` attribute.
     * @param rel_pos Vector that gets per-component multiplied with the `w_size` vector,
     * ultimately defining the window's position
     * @param pivot Pivot of the window
     */
    void fps(ImVec2 &&rel_pos = ImVec2(1.0f, 0.0f), ImVec2 &&pivot = ImVec2(1.0f, 0.0f));

    /**
     * Displays the current window resolution in pixels.
     * @param rel_pos Vector that gets per-component multiplied with the `w_size` vector,
     * ultimately defining the window's position
     * @param pivot Pivot of the window
     */
    void resolution(ImVec2 &&rel_pos = ImVec2(1.0f, 0.05f), ImVec2 &&pivot = ImVec2(1.0f, 0.0f));

    /**
     * Displays currently held down keyboard keys and mouse buttons.
     * @param rel_pos Vector that gets per-component multiplied with the `w_size` vector,
     * ultimately defining the window's position
     * @param pivot Pivot of the window
     */
    void input(ImVec2 &&rel_pos = ImVec2(0.5f, 1.0f), ImVec2 &&pivot = ImVec2(0.5f, 1.0f));

    /**
     * Updates attributes of the GUI class each rendered frame, 
     * before the `render()` method is called.
     */
    virtual void update();

public:
    // If `false`, the `render()` method is skipped 
    bool show_gui = true;

    // If `false`, the `fps()` method is skipped 
    bool show_fps = true;
    // Last FPS value shown on screen
    float last_fps = 0;
    // Interval (in seconds) of calculating a new FPS value 
    double fps_interval = 0.2;
    // Time stamp (in seconds) of the last FPS calculation
    double last_fps_time = 0;

    // If `false`, the `input()` method is skipped 
    bool show_input = true;
    // If `false`, the `resolution()` method is skipped 
    bool show_window_resolution = true;

    // Window size
    glm::u32vec2 w_size;

    /**
     * @param _application_ptr Pointer to the associated `Application`
     */
    GUI(::osi::Application* _application_ptr);

    /**
     * @return Pointer to the associated `Application`
     */
    ::osi::Application* const application() const;

    /**
     * Calls all the rendering functions of the GUI manager.
     */
    virtual void render();
};

}

#endif // GUI_GUI
