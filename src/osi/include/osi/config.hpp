#ifndef OSI_CONFIG
#define OSI_CONFIG

#include <string>

namespace osi
{

/**
 * Struct used to set initial values for `osi` related objects.
 * Edit its attributes to change these values.
 */
struct Config
{
    // NOTE: Could add: min and max time_delta (min for max fps cap, max for smaller lag spike updates)
    //                  warmup iterations to the run loop

    // Initial window width in pixels
    int window_width = 400;
    // Initial window height in pixels
    int window_height = 300;

    // Title in the window header
    std::string window_title = "Merlin Engine";

    // Intialize window to fullscreen
    bool fullscreen = false;
    // Initialize window maximized
    bool maximized = false;
    // Initialize window as resizable
    bool resizable = true;

    virtual ~Config() = default;
};

} // namespace osi

#endif