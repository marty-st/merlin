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

    glm::u32vec2 size_vec;
    bool is_resized;
    bool is_minimized;
    bool has_keyboard_focus;
    bool is_mouse_in_window;
    // glm::vec2 pixel_size; // for uniform sensitivity across resolutions

public:
    Window() = default;
    Window(int window_width, int window_height) 
    : size_vec{glm::u32vec2{window_width, window_height}},
      is_resized{false},
      is_minimized{false},
      has_keyboard_focus{true},
      is_mouse_in_window{true}
    {}

    glm::u32vec2 const& size() const { return size_vec; }
    bool isResized() const { return is_resized; }
    bool isMinimized() const { return is_minimized; }
    bool hasKeyboardFocus() const { return has_keyboard_focus; }
    bool isMouseInWindow() const { return is_mouse_in_window; }

    void resetAfterFrame() { is_resized = false; }
};

} // namespace osi

#endif