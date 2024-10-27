#include <gui/gui.hpp>

#include <osi/gui.hpp>

namespace gui
{

GUI::GUI(::app::Engine* _engine_ptr) 
: engine_ptr{_engine_ptr}
{
    update();
};

::app::Engine* const GUI::engine() const 
{ 
    return engine_ptr; 
}

void GUI::update()
{
    w_size = engine()->window().size();
}

void GUI::render()
{
    if (!show_gui)
        return;

    update();
    fps();
    input();
}

} // namespace gui
