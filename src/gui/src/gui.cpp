#include <gui/gui.hpp>

#include <osi/gui.hpp>

namespace gui
{

GUI::GUI(osi::Application* _application_ptr) 
: application_ptr{_application_ptr}
{
    update();
};

osi::Application* const GUI::application() const 
{ 
    return application_ptr; 
}

float GUI::updateFPS(const double &current_time, const float &dt)
{
    auto fps = last_fps;

    if (current_time - last_fps_time > fps_interval)
    {
        fps = 1.0f / dt;
        last_fps = fps;
        last_fps_time = current_time;
    }

    return fps;
}

void GUI::fps(ImVec2 &&rel_pos, ImVec2 &&pivot)
{
    auto fps = updateFPS(application()->timer().passedSeconds(), application()->timer().dt());

    ImGui::SetNextWindowPos(ImVec2(rel_pos.x * w_size.x, rel_pos.y * w_size.y), ImGuiCond_Always, pivot);

    ImGui::Begin("##FPSCounter", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoBackground 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("%.1f FPS", fps);

    ImGui::End();
}

void GUI::resolution(ImVec2 &&rel_pos, ImVec2 &&pivot)
{
    ImGui::SetNextWindowPos(ImVec2(rel_pos.x * w_size.x, rel_pos.y * w_size.y), ImGuiCond_Always, pivot);

    ImGui::Begin("##WindowResolution", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoBackground 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("%i x %i", w_size.x, w_size.y);

    ImGui::End();
}

void GUI::input(ImVec2 &&rel_pos, ImVec2 &&pivot)
{
    ImGui::SetNextWindowPos(ImVec2(rel_pos.x * w_size.x, rel_pos.y * w_size.y), ImGuiCond_Always, pivot);

    ImGui::Begin("##InputDisplay", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoBackground 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_AlwaysAutoResize);

    for (auto key : application()->keyboard().held())
    {
        ImGui::Text("[%s] ", key.c_str());
        ImGui::SameLine();
    }

    for (auto button : application()->mouse().held())
    {
        ImGui::Text("[%s] ", button.c_str());
        ImGui::SameLine();
    }

    ImGui::End();
}

void GUI::update()
{
    w_size = application()->window().size();
}

void GUI::render()
{
    if (!show_gui)
        return;

    update();

    if (show_fps)
        fps();
    if (show_window_resolution)
        resolution(ImVec2(1.0f, 15.0f / w_size.y));
    if (show_input)
        input();
}

} // namespace gui
