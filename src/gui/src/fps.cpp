#include <gui/gui.hpp>

#include <osi/gui.hpp>

namespace gui
{

float update_fps(GUI* gui, const double &current_time, const float &dt)
{
    auto fps = gui->last_fps;

    if (current_time - gui->last_fps_time > gui->fps_interval)
    {
        fps = 1.0f / dt;
        gui->last_fps = fps;
        gui->last_fps_time = current_time;
    }

    return fps;
}

void GUI::fps()
{
    auto fps = update_fps(this, engine()->timer().passedSeconds(), engine()->timer().dt());

    ImGui::SetNextWindowPos(ImVec2(w_size.x, 0), ImGuiCond_Always, ImVec2(1.0f, 0.0f));

    ImGui::Begin("##FPSCounter", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoBackground 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("FPS: %.1f", fps);

    ImGui::End();
}

} // namespace gui
