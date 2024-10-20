#ifndef OSI_IMGUI_INCLUDE
#define OSI_IMGUI_INCLUDE

#include <osi/gui.hpp>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

namespace osi
{

/**
 * Initializes the ImGui context with connections to SDL2 and OpenGL3.
 */
void IMGUI_start();

/**
 * Prepares ImGui context for a new frame.
 */
void IMGUI_new_frame();

/**
 * Finalizes the ImGui frame, preparing it for render and renders it.
 */
void IMGUI_render();

/**
 * Destroys the ImGui context and its SDL2, OpenGL3 connections.
 */
void IMGUI_finish();

} // namespace osi

#endif // OSI_IMGUI_INCLUDE