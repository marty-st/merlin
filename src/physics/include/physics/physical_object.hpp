#ifndef PHYSICAL_OBJECT_INCLUDE
#define PHYSICAL_OBJECT_INCLUDE

#include <common/object.hpp>

/**
 * Derived from `Object`, represents a physical object in the scene.
 */
class PhysicalObject : public Object
{
    // glm::vec3 velocity = glm::vec3(0.0f);
    // glm::vec3 acceleration = glm::vec3(0.0f);
    // glm::vec3 force = glm::vec3(0.0f);
    // float mass = 1.0f;

public:
    /**
     * Default constructor.
     * @param _frame Pointer to a `Frame`
     */
    PhysicalObject(frame_ptr _frame);

    // glm::vec3 getVelocity() const;
    // glm::vec3 getAcceleration() const;
    // glm::vec3 getForce() const;
    // float getMass() const;

    // void setVelocity(const glm::vec3 _velocity);
    // void setAcceleration(const glm::vec3 _acceleration);
    // void setForce(const glm::vec3 _force);
    // void setMass(const float
};

#endif // PHYSICAL_OBJECT_INCLUDE
