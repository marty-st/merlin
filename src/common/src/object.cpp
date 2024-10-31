#include <common/object.hpp>

Object::Object(frame_ptr _frame)
: 
frame(_frame) 
{}

/**
 * @copydoc Frame::getPositionLocal
 */
glm::vec3 Object::getPositionLocal() const 
{
    return frame->getPositionLocal();
}

/**
 * @copydoc Frame::getRotationLocal
 */
glm::quat Object::getRotationLocal() const 
{
    return frame->getRotationLocal();
}

/**
 * @copydoc Frame::getScaleLocal
 */
glm::vec3 Object::getScaleLocal() const 
{
    return frame->getScaleLocal();
}

/**
 * @copydoc Frame::getRotationAxisXLocal
 */
glm::vec3 Object::getRotationAxisXLocal() const 
{
    return frame->getRotationAxisXLocal();
}

/**
 * @copydoc Frame::getRotationAxisYLocal
 */
glm::vec3 Object::getRotationAxisYLocal() const 
{
    return frame->getRotationAxisYLocal();
}

/**
 * @copydoc Frame::getRotationAxisZLocal
 */
glm::vec3 Object::getRotationAxisZLocal() const 
{
    return frame->getRotationAxisZLocal();
}

/**
 * @copydoc Frame::getTranslationMatLocal
 */
glm::mat4 Object::getTranslationMatLocal() const 
{
    return frame->getTranslationMatLocal();
}

/**
 * @copydoc Frame::getRotationMatLocal
 */
glm::mat4 Object::getRotationMatLocal() const 
{
    return frame->getRotationMatLocal();
}

/**
 * @copydoc Frame::getInverseRotationMatLocal
 */
glm::mat4 Object::getInverseRotationMatLocal() const 
{
    return frame->getInverseRotationMatLocal();
}

/**
 * @copydoc Frame::getScaleMatLocal
 */
glm::mat4 Object::getScaleMatLocal() const 
{
    return frame->getScaleMatLocal();
}

/**
 * @copydoc Frame::getModelMatLocal
 */
glm::mat4 Object::getModelMatLocal() const 
{
    return frame->getModelMatLocal();
}

/**
 * @copydoc Frame::getInverseModelMatLocal
 */
glm::mat4 Object::getInverseModelMatLocal() const 
{
    return frame->getInverseModelMatLocal();
}

/**
 * @copydoc Frame::getPositionWorld
 */
glm::vec3 Object::getPositionWorld() const 
{
    return frame->getPositionWorld();
}

/**
 * @copydoc Frame::getRotationWorld
 */
glm::quat Object::getRotationWorld() const 
{
    return frame->getRotationWorld();
}

/**
 * @copydoc Frame::getScaleWorld
 */
glm::vec3 Object::getScaleWorld() const 
{
    return frame->getScaleWorld();
}

/**
 * @copydoc Frame::getRotationAxisXWorld
 */
glm::vec3 Object::getRotationAxisXWorld() const 
{
    return frame->getRotationAxisXWorld();
}

/**
 * @copydoc Frame::getRotationAxisYWorld
 */
glm::vec3 Object::getRotationAxisYWorld() const 
{
    return frame->getRotationAxisYWorld();
}

/**
 * @copydoc Frame::getRotationAxisZWorld
 */
glm::vec3 Object::getRotationAxisZWorld() const 
{
    return frame->getRotationAxisZWorld();
}

/**
 * @copydoc Frame::getTranslationMatWorld
 */
glm::mat4 Object::getTranslationMatWorld() const 
{
    return frame->getTranslationMatWorld();
}

/**
 * @copydoc Frame::getRotationMatWorld
 */
glm::mat4 Object::getRotationMatWorld() const 
{
    return frame->getRotationMatWorld();
}

/**
 * @copydoc Frame::getInverseRotationMatWorld
 */
glm::mat4 Object::getInverseRotationMatWorld() const 
{
    return frame->getInverseRotationMatWorld();
}

/**
 * @copydoc Frame::getScaleMatWorld
 */
glm::mat4 Object::getScaleMatWorld() const 
{
    return frame->getScaleMatWorld();
}

/**
 * @copydoc Frame::getModelMatWorld
 */
glm::mat4 Object::getModelMatWorld() const 
{
    return frame->getModelMatWorld();
}

/**
 * @copydoc Frame::getInverseModelMatWorld
 */
glm::mat4 Object::getInverseModelMatWorld() const 
{
    return frame->getInverseModelMatWorld();
}

/**
 * @copydoc Frame::getParentModelMatWorld
 */
glm::mat4 Object::getParentModelMatWorld() const 
{
    return frame->getParentModelMatWorld();
}

/**
 * @copydoc Frame::getParentInverseModelMatWorld
 */
glm::mat4 Object::getParentInverseModelMatWorld() const 
{
    return frame->getParentInverseModelMatWorld();
}

/**
 * @copydoc Frame::getParentRotationMatWorld
 */
glm::mat4 Object::getParentRotationMatWorld() const 
{
    return frame->getParentRotationMatWorld();
}

/**
 * @copydoc Frame::getParentInverseRotationMatWorld
 */
glm::mat4 Object::getParentInverseRotationMatWorld() const 
{
    return frame->getParentInverseRotationMatWorld();
}

/**
 * @copydoc Frame::setPosVec
 */
void Object::setPosVec(glm::vec3 _position_vec) 
{
    frame->setPosVec(_position_vec);
}

/**
 * @copydoc Frame::translatePosVec
 */
void Object::translatePosVec(glm::vec3 direction) 
{
    frame->translatePosVec(direction);
}

/**
 * @copydoc Frame::translatePosVec
 */
void Object::translatePosVec(glm::mat4 matrix) 
{
    frame->translatePosVec(matrix);
}

/**
 * @copydoc Frame::normalizeQuat
 */
void Object::normalizeQuat() 
{
    frame->normalizeQuat();
}

/**
 * @copydoc Frame::setRotationQuat
 */
void Object::setRotationQuat(glm::vec3 rotation_vec) 
{
    frame->setRotationQuat(rotation_vec);
}

/**
 * @copydoc Frame::setRotationQuat
 */
void Object::setRotationQuat(glm::quat _rotation_quat) 
{
    frame->setRotationQuat(_rotation_quat);
}

/**
 * @copydoc Frame::setRotationQuat
 */
void Object::setRotationQuat(const glm::mat4 &rotation_matrix) 
{
    frame->setRotationQuat(rotation_matrix);
}

/**
 * @copydoc Frame::rotateRotationQuat
 */
void Object::rotateRotationQuat(glm::vec3 added_rotation) 
{
    frame->rotateRotationQuat(added_rotation);
}

/**
 * @copydoc Frame::rotateRotationQuat
 */
void Object::rotateRotationQuat(glm::quat added_rotation) 
{
    frame->rotateRotationQuat(added_rotation);
}

/**
 * @copydoc Frame::setScale
 */
void Object::setScale(glm::vec3 _scale_vec) 
{
    frame->setScale(_scale_vec);
}

/**
 * @copydoc Frame::setFrame
 */
void Object::setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec) 
{
    frame->setFrame(_position_vec, rotation_vec, _scale_vec);
}

/**
 * @copydoc Frame::setFrame
 */
void Object::setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec) 
{
    frame->setFrame(_position_vec, _rotation_quat, _scale_vec);
}

/**
 * @copydoc Frame::translatePosVecWorld
 */
void Object::translatePosVecWorld(glm::vec3 direction) 
{
    frame->translatePosVecWorld(direction);
}

/**
 * @copydoc Frame::isParentOf
 */
bool Object::isParentOf(frame_ptr other_node) 
{
    return frame->isParentOf(other_node);
}

/**
 * @copydoc Frame::getRootParent
 */
frame_weak_ptr Object::getRootParent() 
{
    return frame->getRootParent();
}

/**
 * @copydoc Frame::getParent
 */
frame_weak_ptr Object::getParent() const 
{
    return frame->getParent();
}

/**
 * @copydoc Frame::getChildren
 */
std::vector<frame_ptr> &Object::getChildren() 
{
    return frame->getChildren();
}

/**
 * @copydoc Frame::addChild
 */
void Object::addChild(frame_ptr child, bool keep_world_transform) 
{
    frame->addChild(child, keep_world_transform);
}

/**
 * @copydoc Frame::removeChild
 */
void Object::removeChild(frame_ptr child) 
{
    frame->removeChild(child);
}

/**
 * @copydoc Frame::setChildren
 */
void Object::setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform) 
{
    frame->setChildren(_children, keep_world_transform);
}

/**
 * @copydoc Frame::removeChildren
 */
void Object::removeChildren(const std::vector<frame_ptr> &unwanted_children) 
{
    frame->removeChildren(unwanted_children);
}

/**
 * @copydoc Frame::clearChildren
 */
void Object::clearChildren() 
{
    frame->clearChildren();
}

/**
 * @copydoc Frame::extendChildren
 */
void Object::extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform) 
{
    frame->extendChildren(extra_children, keep_world_transform);
}

/**
 * @copydoc Frame::transferChild
 */
void Object::transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform) 
{
    frame->transferChild(child, new_parent, keep_world_transform);
}
