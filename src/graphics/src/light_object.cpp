#include <graphics/light_object.hpp>

LightObject::LightObject(frame_ptr _frame, light_ptr _light)
: Object(_frame)
, light(_light)
{}
