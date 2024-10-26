#ifndef OSI_CONFIG
#define OSI_CONFIG

#include <string>

namespace osi
{

struct Config
{
    // NOTE: Could add: min and max time_delta (min for max fps cap, max for smaller lag spike updates)
    //                  warmup iterations to the run loop

    // Initial window width in pixels
    int window_width = 400;
    // Initial window height in pixels
    int window_height = 300;

    std::string window_title = "Merlin Engine";

    bool fullscreen = false;
    // bool maximized = false;
    bool resizable = true;

    virtual ~Config() = default;
};

} // namespace osi

#endif