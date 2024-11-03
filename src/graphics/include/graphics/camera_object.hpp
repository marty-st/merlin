#ifndef CAMERA_OBJECT_INCLUDE
#define CAMERA_OBJECT_INCLUDE

#include <common/object.hpp>

/**
 * Derived from `Object`, represents a camera object in the scene.
 */
class CameraObject : public Object
{
    // Camera's front and up vectors
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Camera's field of view, aspect ratio, near and far planes
    float fov;
    float aspect_ratio;
    float near;
    float far;

    // TO DO: Implement orthographic projection and orbital camera type
    // // Perspective or orthographic
    // bool perspective = true;
    // // Camera type
    // CameraType type = CameraType::FPS;

public:
    /**
     * Default constructor.
     * @param _frame Pointer to a `Frame`
     * @param _fov Field of view in degrees
     * @param _aspect_ratio Aspect ratio of the camera
     * @param _near Near plane of the view frustum
     * @param _far Far plane of the view frustum
     */
    CameraObject(frame_ptr _frame, 
                 const float _fov, 
                 const float _aspect_ratio, 
                 const float _near = 0.1f, 
                 const float _far = 100.0f);

    /**
     * @return Camera's front vector
     */
    glm::vec3 getFront() const;

    /**
     * @return Camera's up vector
     */
    glm::vec3 getUp() const;

    /**
     * @return Camera's field of view in degrees
     */
    float getFOV() const;

    /**
     * @return Camera's aspect ratio
     */
    float getAspectRatio() const;

    /**
     * @return View frustum's near plane distance
     */
    float getNear() const;

    /**
     * @return View frustum's far plane distance
     */
    float getFar() const;

    /**
     * Sets the camera's front vector.
     * @param _front New front vector
     */
    void setFront(const glm::vec3 _front);

    /**
     * Sets the camera's up vector.
     * @param _up New up vector
     */
    void setUp(const glm::vec3 _up);

    /**
     * Sets the camera's field of view in degrees.
     * @param _fov New field of view
     */
    void setFOV(const float _fov);

    /**
     * Sets the camera's aspect ratio.
     * @param _aspect_ratio New aspect ratio
     */
    void setAspectRatio(const float _aspect_ratio);

    /**
     * Sets the view frustum's near plane distance.
     * @param _near New near plane distance
     */
    void setNear(const float _near);

    /**
     * Sets the view frustum's far plane distance.
     * @param _far New far plane distance
     */
    void setFar(const float _far);

    // bool isPerspective() const;
    // CameraType getType() const;
    // void setPerspective(bool _perspective);
    // void setType(CameraType _type);
    // void setOrthographic(float left, float right, float bottom, float top, float near, float far);

    /**
     * @return Camera's view matrix
     */
    glm::mat4 getViewMatrix() const;

    /**
     * @return Camera's projection matrix
     */
    glm::mat4 getProjectionMatrix() const;

    /**
     * @return Camera's view-projection matrix
     */
    glm::mat4 getViewProjectionMatrix() const;
};

#endif // CAMERA_OBJECT_INCLUDE
