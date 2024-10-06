#ifndef SDL_INCLUDE
#define SDL_INCLUDE

#include <SDL2/SDL.h>

#include <cstdint>

namespace osi
{

// Initial window size in pixels
const int screen_width = 400;
const int screen_height = 300;

static SDL_Window* window_ptr = nullptr;
static SDL_GLContext gl_context_ptr = nullptr;

void SDL_error(const char* message);
bool init_SDL(uint8_t option);
void setup_SDL_GL_attributes();
void setup_SDL_window(const int screen_width, const int screen_height);
void setup_SDL_GL_context();
void SDL_start();
void SDL_run(bool &running);
void SDL_finish();

} // namespace osi

#endif