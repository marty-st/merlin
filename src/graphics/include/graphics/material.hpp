#ifndef MATERIAL_INCLUDE
#define MATERIAL_INCLUDE

#include <util/math.hpp>

struct Material
{
    // Ambient color. Contains skybox reflection (or other information) in .w element
    glm::vec4 ambient_color;
    // Diffuse/Albedo color. Contains Opacity in .w element
    glm::vec4 diffuse_color;
    // Specular color. Contains shininess in .w element
    glm::vec4 specular_color;

    Material();

    Material(glm::vec4 _ambient_color, glm::vec4 _diffuse_color, glm::vec4 _specular_color);
};

#endif // MATERIAL_INCLUDE
