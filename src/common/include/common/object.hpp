#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE

#include <common/frame.hpp>

class Object
{
    frame_ptr frame;

public:
    /**
     * @copydoc Frame::getPositionLocal
     */
    glm::vec3 getPositionLocal() const;

    /**
     * @copydoc Frame::getRotationLocal
     */
    glm::quat getRotationLocal() const;

    /**
     * @copydoc Frame::getScaleLocal
     */
    glm::vec3 getScaleLocal() const;

    /**
     * @copydoc Frame::getRotationAxisXLocal
     */
    glm::vec3 getRotationAxisXLocal() const;

    /**
     * @copydoc Frame::getRotationAxisYLocal
     */
    glm::vec3 getRotationAxisYLocal() const;

    /**
     * @copydoc Frame::getRotationAxisZLocal
     */
    glm::vec3 getRotationAxisZLocal() const;

    /**
     * @copydoc Frame::getTranslationMatLocal
     */
    glm::mat4 getTranslationMatLocal() const;

    /**
     * @copydoc Frame::getRotationMatLocal
     */
    glm::mat4 getRotationMatLocal() const;

    /**
     * @copydoc Frame::getInverseRotationMatLocal
     */
    glm::mat4 getInverseRotationMatLocal() const;

    /**
     * @copydoc Frame::getScaleMatLocal
     */
    glm::mat4 getScaleMatLocal() const;

    /**
     * @copydoc Frame::getModelMatLocal
     */
    glm::mat4 getModelMatLocal() const;

    /**
     * @copydoc Frame::getInverseModelMatLocal
     */
    glm::mat4 getInverseModelMatLocal() const;

    /**
     * @copydoc Frame::getPositionWorld
     */
    glm::vec3 getPositionWorld() const;

    /**
     * @copydoc Frame::getRotationWorld
     */
    glm::quat getRotationWorld() const;

    /**
     * @copydoc Frame::getScaleWorld
     */
    glm::vec3 getScaleWorld() const;

    /**
     * @copydoc Frame::getRotationAxisXWorld
     */
    glm::vec3 getRotationAxisXWorld() const;

    /**
     * @copydoc Frame::getRotationAxisYWorld
     */
    glm::vec3 getRotationAxisYWorld() const;

    /**
     * @copydoc Frame::getRotationAxisZWorld
     */
    glm::vec3 getRotationAxisZWorld() const;

    /**
     * @copydoc Frame::getTranslationMatWorld
     */
    glm::mat4 getTranslationMatWorld() const;

    /**
     * @copydoc Frame::getRotationMatWorld
     */
    glm::mat4 getRotationMatWorld() const;

    /**
     * @copydoc Frame::getInverseRotationMatWorld
     */
    glm::mat4 getInverseRotationMatWorld() const;

    /**
     * @copydoc Frame::getScaleMatWorld
     */
    glm::mat4 getScaleMatWorld() const;

    /**
     * @copydoc Frame::getModelMatWorld
     */
    glm::mat4 getModelMatWorld() const;

    /**
     * @copydoc Frame::getInverseModelMatWorld
     */
    glm::mat4 getInverseModelMatWorld() const;

    /**
     * @copydoc Frame::getParentModelMatWorld
     */
    glm::mat4 getParentModelMatWorld() const;

    /**
     * @copydoc Frame::getParentInverseModelMatWorld
     */
    glm::mat4 getParentInverseModelMatWorld() const;

    /**
     * @copydoc Frame::getParentRotationMatWorld
     */
    glm::mat4 getParentRotationMatWorld() const;

    /**
     * @copydoc Frame::getParentInverseRotationMatWorld
     */
    glm::mat4 getParentInverseRotationMatWorld() const;

    /**
     * @copydoc Frame::setPosVec
     */
    void setPosVec(glm::vec3 _position_vec);

    /**
     * @copydoc Frame::translatePosVec
     */
    void translatePosVec(glm::vec3 direction);

    /**
     * @copydoc Frame::translatePosVec
     */
    void translatePosVec(glm::mat4 matrix);

    /**
     * @copydoc Frame::normalizeQuat
     */
    void normalizeQuat();

    /**
     * @copydoc Frame::setRotationQuat
     */
    void setRotationQuat(glm::vec3 rotation_vec);

    /**
     * @copydoc Frame::setRotationQuat
     */
    void setRotationQuat(glm::quat _rotation_quat);

    /**
     * @copydoc Frame::setRotationQuat
     */
    void setRotationQuat(const glm::mat4 &rotation_matrix);

    /**
     * @copydoc Frame::rotateRotationQuat
     */
    void rotateRotationQuat(glm::vec3 added_rotation);

    /**
     * @copydoc Frame::rotateRotationQuat
     */
    void rotateRotationQuat(glm::quat added_rotation);

    /**
     * @copydoc Frame::setScale
     */
    void setScale(glm::vec3 _scale_vec);

    /**
     * @copydoc Frame::setFrame
     */
    void setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec);

    /**
     * @copydoc Frame::setFrame
     */
    void setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec);

    /**
     * @copydoc Frame::translatePosVecWorld
     */
    void translatePosVecWorld(glm::vec3 direction);

    /**
     * @copydoc Frame::isParentOf
     */
    bool isParentOf(frame_ptr other_node);

    /**
     * @copydoc Frame::getRootParent
     */
    frame_weak_ptr getRootParent();

    /**
     * @copydoc Frame::getParent
     */
    frame_weak_ptr getParent() const;

    /**
     * @copydoc Frame::getChildren
     */
    std::vector<frame_ptr> &getChildren();

    /**
     * @copydoc Frame::addChild
     */
    void addChild(frame_ptr child, bool keep_world_transform = true);

    /**
     * @copydoc Frame::removeChild
     */
    void removeChild(frame_ptr child);

    /**
     * @copydoc Frame::setChildren
     */
    void setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform = true);

    /**
     * @copydoc Frame::removeChildren
     */
    void removeChildren(const std::vector<frame_ptr> &unwanted_children);

    /**
     * @copydoc Frame::clearChildren
     */
    void clearChildren();

    /**
     * @copydoc Frame::extendChildren
     */
    void extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform = true);

    /**
     * @copydoc Frame::transferChild
     */
    void transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform = true);
};

#endif // OBJECT_INCLUDE
