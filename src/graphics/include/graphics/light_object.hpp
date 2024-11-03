#ifndef LIGHT_OBJECT_INCLUDE
#define LIGHT_OBJECT_INCLUDE

#include <common/object.hpp>
#include <graphics/light.hpp>

/**
 * Derived from `Object`. Represents a light object in the scene.
 */
class LightObject : public Object
{
    light_ptr light = nullptr;

    // Possibility for animation properties, etc.

public:
    /**
     * Default constructor.
     * @param _frame Pointer to a `Frame`
     * @param _light Shared pointer to a `Light`
     */
    LightObject(frame_ptr _frame, light_ptr _light);
};

#endif // LIGHT_OBJECT_INCLUDE
