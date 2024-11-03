#ifndef LIGHT_INCLUDE
#define LIGHT_INCLUDE

#include <util/math.hpp>

#include <memory>

class Light;

using light_ptr = std::shared_ptr<Light>;

/**
 * Represents a light in the scene.
 */
class Light
{
    // the .w component holds information about range. If .w == 0, it's a directional light
    glm::vec4 ambient_color;
    // thw .w component holds information about attenuation drop-off.
    glm::vec4 diffuse_color;
    // the .w component has no use as of now
    glm::vec4 specular_color;
    // if direction.w == 0, it's a point light
    glm::vec4 direction;

    // How to recognize different types of lights:
    // 1. Point light: direction.w == 0 (no direction)
    // 2. Directional light: direction.w != 0 and ambient_color.w == 0 (has direction and no range)
    // 3. Spot light: direction.w != 0 and ambient_color.w != 0 (has direction and range)
    // 
    // In other words:
    // 1. Point light: has attenuation, range, NO direction (2:1)
    // 2. Directional light: has direction, NO attenuation, NO range (1:2)
    // 3. Spot light: has direction, cone attenuation, range (3:0)

    /**
     * Default constructor.
     * @param _ambient_color Ambient color of the light. .w used for range
     * @param _diffuse_color Diffuse color of the light. .w used for attenuation drop-off
     * @param _specular_color Specular color of the light
     * @param _direction Direction of the light. .w == 0 for point lights, 
     * .w != 0 for spotlights and directional lights
     */
    Light(const glm::vec4 &_ambient_color, 
          const glm::vec4 &_diffuse_color, 
          const glm::vec4 &_specular_color, 
          const glm::vec4 &_direction);
public:
    /**
     * Creates a point light.
     * @param _ambient_color Ambient color of the light.
     * @param _diffuse_color Diffuse color of the light.
     * @param _specular_color Specular color of the light
     * @param range Range of the light
     * @param attenuation Attenuation drop-off of the light
     * @return Shared pointer to the point light
     */
    static light_ptr createPointLight(const glm::vec3 &_ambient_color, 
                                      const glm::vec3 &_diffuse_color, 
                                      const glm::vec3 &_specular_color,
                                      float range,
                                      float attenuation = 1.0f
        );

    /**
     * Creates a directional light.
     * @param _ambient_color Ambient color of the light.
     * @param _diffuse_color Diffuse color of the light.
     * @param _specular_color Specular color of the light
     * @param direction Direction of the light
     * @return Shared pointer to the directional light
     */
    static light_ptr createDirectionalLight(const glm::vec3 &_ambient_color, 
                                            const glm::vec3 &_diffuse_color, 
                                            const glm::vec3 &_specular_color,
                                            const glm::vec3 &direction
        );

    /**
     * Creates a spotlight.
     * @param _ambient_color Ambient color of the light.
     * @param _diffuse_color Diffuse color of the light.
     * @param _specular_color Specular color of the light
     * @param direction Direction of the cone
     * @param range Range of the light
     * @param attenuation Attenuation drop-off of the cone
     * @return Shared pointer to the spotlight
     */
    static light_ptr createSpotLight(const glm::vec3 &_ambient_color, 
                                     const glm::vec3 &_diffuse_color, 
                                     const glm::vec3 &_specular_color,
                                     const glm::vec3 &direction,
                                     float range,
                                     float attenuation = 1.0f
        );
    // static createAmbientLight();
    // static createAreaLight();
};

#endif // LIGHT_INCLUDE