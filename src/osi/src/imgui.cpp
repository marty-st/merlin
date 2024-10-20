#include <osi/imgui.hpp>
#include <osi/sdl.hpp>

namespace osi
{

void IMGUI_start()
{
    ImGui::CreateContext();
    // Needs to be called, because window_ptr, gl_context_ptr is not known here (static)
    SDL_init_ImGui();
    ImGui_ImplOpenGL3_Init();
}

void IMGUI_new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void IMGUI_render()
{
    // Finalizes the frame so DrawData() can be called
    ImGui::Render();
    // Renders ImGui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGUI_finish()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

} // namespace osi
