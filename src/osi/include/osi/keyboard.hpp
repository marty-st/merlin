#ifndef OSI_KEYBOARD_INCLUDE
#define KEYBOARD_INCLUDE

#include <string>
#include <unordered_set>

namespace osi
{

void SDL_keyboard_event(const SDL_KeyboardEvent &);
void SDL_text_input_event(const SDL_TextInputEvent &);

/**
 * Encapsulates SDL Keyboard events.
 */
class Keyboard
{
    // friend trick to allow run loop to access attributes directly
    friend void ::osi::SDL_keyboard_event(const SDL_KeyboardEvent &);
    friend void ::osi::SDL_text_input_event(const SDL_TextInputEvent &);

    // Keys pressed down in the current loop iteration 
    std::unordered_set<std::string> just_pressed = {};
    // Keys released in the current loop iteration
    std::unordered_set<std::string> just_released = {};
    // Keys that were pressed in the current or any previous loop iteration and not released yet
    std::unordered_set<std::string> held_down = {};
    // String of UTF-8 characters inputted via keyboard
    std::string unicode_text = "";

public:
    Keyboard() = default;

    /**
     * @return Set of keys pressed down in the current loop iteration
     */
    std::unordered_set<std::string> const& pressed() const { return just_pressed; }

    /**
     * @return Set of keys released in the current loop iteration
     */
    std::unordered_set<std::string> const& released() const { return just_released; }

    /**
     * @return Set of keys that were pressed in the current or any previous loop iteration
     *  and not released yet
     */
    std::unordered_set<std::string> const& held() const { return held_down; }

    /**
     * @return String of UTF-8 characters inputted via keyboard
     */
    std::string const& text() const { return unicode_text; }

    /**
     * Resets attributes which were relevant only for a single frame.
     */
    void resetAfterFrame()
    {
        just_pressed.clear();
        just_released.clear();
        unicode_text.clear();
    }
};

} // namespace osi

#endif // OSI_KEYBOARD_INCLUDE
