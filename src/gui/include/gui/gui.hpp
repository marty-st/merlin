#ifndef GUI_GUI
#define GUI_GUI

#include <app/engine.hpp>
#include <util/math.hpp>

namespace gui
{

class GUI
{
    ::app::Engine* engine_ptr = nullptr;

    void update();

    void fps();
    void input();

public:
    bool show_gui = true;

    float last_fps = 0;
    double fps_interval = 0.2;
    double last_fps_time = 0;

    glm::u32vec2 w_size;

    GUI(::app::Engine* _engine_ptr);

    ::app::Engine* const engine() const;

    void render();

};

}

#endif // GUI_GUI
