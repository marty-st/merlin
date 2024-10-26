#ifndef ENGINE_INCLUDE
#define ENGINE_INCLUDE

#include <osi/application.hpp>

namespace app
{

class Engine : public osi::Application
{
    void update() override {}
    void render() override {}
public:
    Engine(const osi::ApplicationConfig &app_cfg);
    ~Engine() = default;
};

} // namespace app

#endif