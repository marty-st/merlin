#ifndef GUI_GUI
#define GUI_GUI

#include <app/engine.hpp>

namespace gui
{

class GUI
{
    ::app::Engine* engine_ptr = nullptr;

    void fps();

public:
    bool show_gui = true;

    float last_fps = 0;
    double fps_interval = 0.2;
    double last_fps_time = 0;

    GUI(::app::Engine* _engine_ptr) : engine_ptr{_engine_ptr} {};

    ::app::Engine* const engine() const { return engine_ptr; }

    void render();

};

}

#endif // GUI_GUI
