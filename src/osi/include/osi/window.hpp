#ifndef OSI_WINDOW_INCLUDE
#define OSI_WINDOW_INCLUDE

#include <util/math.hpp>

namespace osi
{

void SDL_window_event(const SDL_WindowEvent &);

class Window
{
    // friend trick, so there is no need to make setter methods
    // Eventually, when in-app options will allow to change these
    // parameters, setters might be necessary. If so, delete this. 
    friend void ::osi::SDL_window_event(const SDL_WindowEvent &);

    // Window size in x, y coordinates
    glm::u32vec2 size_vec;
    // Window was resized this frame
    bool is_resized;
    // Window is minimized
    bool is_minimized;
    // Window has keyboard focus
    bool has_keyboard_focus;
    // Mouse is hovering within the window
    bool is_mouse_in_window;
    // Pixel size in real world measurement (meters)
    // glm::vec2 pixel_size; // for uniform sensitivity across resolutions

public:
    Window(int window_width, int window_height) 
    : size_vec{glm::u32vec2{window_width, window_height}},
      is_resized{false},
      is_minimized{false},
      has_keyboard_focus{true},
      is_mouse_in_window{true}
    {}

    /**
     * @return Size of window in pixels as a vec2.
     */
    glm::u32vec2 const& size() const { return size_vec; }

    /**
     * @return `true` if window was resized this frame, `false` otherwise
     */
    bool isResized() const { return is_resized; }

    /**
     * @return `true` if window is currently minimized, `false` otherwise
     */
    bool isMinimized() const { return is_minimized; }

    /**
     * @return `true` if window has keyboard focus, `false` otherwise
     */
    bool hasKeyboardFocus() const { return has_keyboard_focus; }

    /**
     * @return `true` if mouse is hovering within the window, `false` otherwise
     */
    bool isMouseInWindow() const { return is_mouse_in_window; }

    /**
     * Resets attributes which were toggled and relevant only for a single frame.
     */
    void resetAfterFrame() { is_resized = false; }
};

} // namespace osi

#endif