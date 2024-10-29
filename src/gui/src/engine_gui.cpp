#include <gui/engine_gui.hpp>

namespace gui
{

EngineGUI::EngineGUI(::app::Engine* _engine_ptr)
: GUI(_engine_ptr), engine_ptr{_engine_ptr}
{
    update();
};

app::Engine* const EngineGUI::engine() const 
{ 
    return engine_ptr; 
}

void EngineGUI::update() 
{ 
    GUI::update();
}

void EngineGUI::render()
{
    GUI::render();
}

} // namespace gui
 