#include <graphics/light.hpp>

Light::Light(const glm::vec4 &_ambient_color, 
             const glm::vec4 &_diffuse_color, 
             const glm::vec4 &_specular_color, 
             const glm::vec4 &_direction)
    : ambient_color(_ambient_color),
      diffuse_color(_diffuse_color),
      specular_color(_specular_color),
      direction(_direction)
{}

light_ptr Light::createPointLight(const glm::vec3 &_ambient_color, 
    const glm::vec3 &_diffuse_color, 
    const glm::vec3 &_specular_color,
    float range,
    float attenuation
    )
{
    return light_ptr{ new Light(glm::vec4(_ambient_color, range),
        glm::vec4(_diffuse_color, attenuation),
        glm::vec4(_specular_color, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) };
}

light_ptr Light::createDirectionalLight(const glm::vec3 &_ambient_color, 
    const glm::vec3 &_diffuse_color, 
    const glm::vec3 &_specular_color,
    const glm::vec3 &direction
    )
{
    return light_ptr{ new Light(glm::vec4(_ambient_color, 0.0f),
        glm::vec4(_diffuse_color, 1.0f),
        glm::vec4(_specular_color, 1.0f),
        glm::vec4(direction, 1.0f)) };
}

light_ptr Light::createSpotLight(const glm::vec3 &_ambient_color, 
    const glm::vec3 &_diffuse_color, 
    const glm::vec3 &_specular_color,
    const glm::vec3 &direction,
    float range,
    float attenuation
    )
{
    return light_ptr{ new Light(glm::vec4(_ambient_color, range),
        glm::vec4(_diffuse_color, attenuation),
        glm::vec4(_specular_color, 1.0f),
        glm::vec4(direction, 1.0f)) };
}
