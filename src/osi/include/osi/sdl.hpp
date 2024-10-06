#ifndef SDL_INCLUDE
#define SDL_INCLUDE

#include <cstdint>

void SDL_error(const char* message);
bool init_SDL(uint8_t option);
void setup_SDL_GL_attributes();
SDL_Window* setup_SDL_window(const int screen_width, const int screen_height);
SDL_GLContext setup_SDL_GL_context(SDL_Window* window_ptr);

#endif