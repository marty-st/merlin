#include <graphics/camera_object.hpp>

CameraObject::CameraObject(frame_ptr _frame, 
                           const float _fov, 
                           const float _aspect_ratio, 
                           const float _near, 
                           const float _far)
: Object(_frame)
, fov(_fov)
, aspect_ratio(_aspect_ratio)
, near(_near)
, far(_far)
{
}

glm::vec3 CameraObject::getFront() const
{
    return front;
}

glm::vec3 CameraObject::getUp() const
{
    return up;
}

float CameraObject::getFOV() const
{
    return fov;
}

float CameraObject::getAspectRatio() const
{
    return aspect_ratio;
}

float CameraObject::getNear() const
{
    return near;
}

float CameraObject::getFar() const
{
    return far;
}

void CameraObject::setFront(const glm::vec3 _front)
{
    front = _front;
}

void CameraObject::setUp(const glm::vec3 _up)
{
    up = _up;
}

void CameraObject::setFOV(const float _fov)
{
    fov = _fov;
}

void CameraObject::setAspectRatio(const float _aspect_ratio)
{
    aspect_ratio = _aspect_ratio;
}

void CameraObject::setNear(const float _near)
{
    near = _near;
}

void CameraObject::setFar(const float _far)
{
    far = _far;
}

glm::mat4 CameraObject::getViewMatrix() const
{
    return glm::lookAt(frame->getPositionWorld(), 
                       frame->getPositionWorld() + front, 
                       up);
}

glm::mat4 CameraObject::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

glm::mat4 CameraObject::getViewProjectionMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
}
