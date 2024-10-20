#ifndef OSI_MOUSE_INCLUDE
#define OSI_MOUSE_INCLUDE

#include <util/math.hpp>
#include <string>
#include <unordered_set>

namespace osi
{

void SDL_mouse_event(const SDL_Event &);

/**
 * Encapsulates SDL Mouse events.
 */
class Mouse
{
    // friend trick to allow run loop to access attributes directly
    friend void ::osi::SDL_mouse_event(const SDL_Event &);

    // Mouse coordinates relative to SDL window
    glm::i32vec2 position = {0, 0};
    // Difference in mouse coordinates compared to previous iteration
    glm::i32vec2 position_delta = {0, 0};
    // Buttons pressed down in the current loop iteration 
    std::unordered_set<std::string> just_pressed = {};
    // Buttons released in the current loop iteration
    std::unordered_set<std::string> just_released = {};
    // Buttons that were pressed in the current or any previous loop iteration and not released yet
    std::unordered_set<std::string> held_down = {};

public:
    Mouse() = default;

    /**
     * @return Coordinates (x,y) of the mouse relative to SDL window
     */
    glm::i32vec2 const& pos() const { return position; }

    /**
     * @return Relative coordinates (x,y) of the mouse relative to SDL window
     */
    glm::i32vec2 const& posDelta() const { return position_delta; }

    /**
     * @return Set of buttons pressed down in the current loop iteration
     */
    std::unordered_set<std::string> const& pressed() const { return just_pressed; }

    /**
     * @return Set of buttons released in the current loop iteration
     */
    std::unordered_set<std::string> const& released() const { return just_released; }

    /**
     * @return Set of buttons that were pressed in the current or any previous loop iteration
     *  and not released yet
     */
    std::unordered_set<std::string> const& held() const { return held_down; }

    void resetAfterFrame()
    {
        just_pressed.clear();
        just_released.clear();
        position_delta.x = 0;
        position_delta.y = 0;
    }
};

} // namespace osi

#endif