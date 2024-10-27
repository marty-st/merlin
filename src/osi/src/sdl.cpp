#include <osi/sdl.hpp>
#include <osi/imgui.hpp>

#include <stdexcept>
#include <string>

namespace osi
{

static std::string to_key_name(SDL_Keycode const code)
{
    std::string name { SDL_GetKeyName(code) };
    name.erase(std::remove_if(name.begin(), name.end(), isspace), name.end());
    return name;
}

static std::string to_button_name(std::uint8_t const button_index)
{
    switch (button_index)
    {
        case SDL_BUTTON_LEFT: return "MouseLeft";
        case SDL_BUTTON_RIGHT: return "MouseRight";
        case SDL_BUTTON_MIDDLE: return "MouseMiddle";
        case SDL_BUTTON_X1: return "MouseWheelUp";
        case SDL_BUTTON_X2: return "MouseWheelDown";
        default: return "MouseUNKNOWN";
    }
}

void SDL_error(const char* message)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                 (std::string(message) + std::string(": %s")).c_str(),
                 SDL_GetError());
}

bool init_SDL(uint8_t option)
{
    // Returns 0 on success
    if (SDL_Init(option))
    {
        SDL_error("Could not initialize SDL2");
        return false;
    }
    
    return true;
}

void setup_SDL_GL_attributes()
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_GLattr
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

void setup_SDL_window(SDLConfig &sdl_cfg)
{
    // Description: https://wiki.libsdl.org/SDL2/SDL_WindowFlags
    window_ptr = SDL_CreateWindow(sdl_cfg.window_title.c_str(), 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED,
                                          sdl_cfg.window_width,
                                          sdl_cfg.window_height,
                                          SDL_WINDOW_OPENGL 
                                          | (sdl_cfg.fullscreen 
                                            ? SDL_WINDOW_FULLSCREEN_DESKTOP 
                                            : (sdl_cfg.resizable 
                                               ? SDL_WINDOW_RESIZABLE 
                                               : SDL_WINDOW_BORDERLESS)
                                            )
                                 );

    if (!window_ptr)
    {
        SDL_error("Could not create window: %s");
        throw;
    }
}

void setup_SDL_GL_context()
{
    gl_context_ptr = SDL_GL_CreateContext(window_ptr);
    if (!gl_context_ptr)
    {
        SDL_error("Could not create OpenGL context: %s"); 
        throw;
    }
}

void SDL_init_ImGui()
{
    ImGui_ImplSDL2_InitForOpenGL(window_ptr, gl_context_ptr);
}

void SDL_start(SDLConfig &sdl_cfg)
{
    setup_SDL_GL_attributes();

    // Initialize SDL video subsystem
    if (!init_SDL(SDL_INIT_VIDEO))
        throw std::runtime_error("Error: Initialisation of the SDL2 library has FAILED.");

    // Setup SDL Window
    setup_SDL_window(sdl_cfg);
    if (!window_ptr)
        throw std::runtime_error("Error: The call 'SDL_CreateWindow' function has FAILED.");

    // Setup OpenGL context
    setup_SDL_GL_context();
    if (!gl_context_ptr)
        throw std::runtime_error("Error: The call 'SDL_GL_CreateContext' function has FAILED.");

}

void link_pointers_to_SDL(Keyboard* _keyboard, Mouse* _mouse, Window* _window)
{
    keyboard = _keyboard;
    mouse = _mouse;
    window = _window;
}

void SDL_window_event(const SDL_WindowEvent &window_event)
{
    switch (window_event.event)
    {
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            {
                window->size_vec.x = window_event.data1; 
                window->size_vec.y = window_event.data2;
                window->is_resized = true; 
            }
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            window->is_minimized = true; 
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
        case SDL_WINDOWEVENT_RESTORED:
            window->is_minimized = false; 
            break;
        case SDL_WINDOWEVENT_ENTER:
            window->is_mouse_in_window = true; 
            break;
        case SDL_WINDOWEVENT_LEAVE:
            window->is_mouse_in_window = false; 
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            window->has_keyboard_focus = true; 
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            window->has_keyboard_focus = false; 
            break;
        default: break;
    }
}

void SDL_keyboard_event(const SDL_KeyboardEvent & keyboard_event)
{
    if (ImGui::GetIO().WantCaptureKeyboard)
        return;

    switch (keyboard_event.type)
    {
        case SDL_KEYDOWN:
        {
            std::string const name = to_key_name(keyboard_event.keysym.sym);
            keyboard->just_pressed.insert(name);
            keyboard->held_down.insert(name);
            break;
        }
        case SDL_KEYUP:
        {
            std::string const name = to_key_name(keyboard_event.keysym.sym);
            keyboard->just_released.insert(name);
            keyboard->held_down.erase(name);
            break;
        }
    }
}

void SDL_text_input_event(const SDL_TextInputEvent &text_event)
{
    if (ImGui::GetIO().WantCaptureKeyboard)
        return;
        
    keyboard->unicode_text += text_event.text;
}

void SDL_mouse_event(const SDL_Event &event)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    switch (event.type)
    {
        case SDL_MOUSEMOTION:
            mouse->position.x = event.motion.x;
            mouse->position.y = event.motion.y;
            mouse->position_delta.x = event.motion.xrel;
            mouse->position_delta.y = event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            std::string const name = to_button_name(event.button.button);
            mouse->just_pressed.insert(name);
            mouse->held_down.insert(name);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            std::string const name = to_button_name(event.button.button);
            mouse->just_released.insert(name);
            mouse->held_down.erase(name);
            break;
        }
        case SDL_MOUSEWHEEL:
            if(event.wheel.y > 0) // scroll up
            {
                std::string const name = to_button_name(SDL_BUTTON_X1);
                mouse->just_pressed.insert(name);
            }
            else if(event.wheel.y < 0) // scroll down
            {
                std::string const name = to_button_name(SDL_BUTTON_X2);
                mouse->just_pressed.insert(name);
            }
            break;
    }
}

void SDL_swap_buffer()
{
    SDL_GL_SwapWindow(window_ptr);
}

void SDL_run(bool &running)
{
    SDL_Event event;

    // Loop until there are no more pending events to process
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                running = false; // Stop running if the window is closed
                break;
            case SDL_WINDOWEVENT:
                SDL_window_event(event.window);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                SDL_keyboard_event(event.key);
                break;
            case SDL_TEXTINPUT:
                SDL_text_input_event(event.text);
                break;
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
                SDL_mouse_event(event);
                break;
            default:
                break;
        }
    }
}

void SDL_finish()
{
    if (gl_context_ptr != nullptr)
    {
        SDL_GL_DeleteContext(gl_context_ptr);
        gl_context_ptr = nullptr;
    }

    SDL_DestroyWindow(window_ptr);
    window_ptr = nullptr;

    SDL_Quit();
}

} // namespace osi
