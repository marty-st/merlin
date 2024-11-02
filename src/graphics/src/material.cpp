#include <graphics/material.hpp>

Material::Material()
{
    ambient_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    diffuse_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    specular_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
}

Material::Material(glm::vec4 _ambient_color, glm::vec4 _diffuse_color, glm::vec4 _specular_color)
: ambient_color{_ambient_color}
, diffuse_color{_diffuse_color}
, specular_color{_specular_color}
{}
