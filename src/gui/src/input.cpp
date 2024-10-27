#include <gui/gui.hpp>

#include <osi/gui.hpp>

namespace gui
{

void GUI::input()
{
    ImGui::SetNextWindowPos(ImVec2(0.5 * w_size.x, w_size.y), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

    ImGui::Begin("##InputDisplay", 
        nullptr, 
        ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoBackground 
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_AlwaysAutoResize);

    for (auto key : engine()->keyboard().held())
    {
        ImGui::Text("[%s] ", key.c_str());
        ImGui::SameLine();
    }

    for (auto button : engine()->mouse().held())
    {
        ImGui::Text("[%s] ", button.c_str());
        ImGui::SameLine();
    }

    ImGui::End();
}

} // namespace gui
