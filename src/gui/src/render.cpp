#include <gui/gui.hpp>

#include <osi/gui.hpp>

namespace gui
{

void GUI::render()
{
    if (!show_gui)
        return;

    fps();
}

} // namespace gui
