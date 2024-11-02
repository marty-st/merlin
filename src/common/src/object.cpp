#include <common/object.hpp>

Object::Object(frame_ptr _frame)
: 
frame(_frame) 
{}

frame_ptr Object::getFrame() const
{
    return frame;
}

glm::vec3 Object::getPositionLocal() const 
{
    return frame->getPositionLocal();
}

glm::quat Object::getRotationLocal() const 
{
    return frame->getRotationLocal();
}

glm::vec3 Object::getScaleLocal() const 
{
    return frame->getScaleLocal();
}

glm::vec3 Object::getRotationAxisXLocal() const 
{
    return frame->getRotationAxisXLocal();
}

glm::vec3 Object::getRotationAxisYLocal() const 
{
    return frame->getRotationAxisYLocal();
}

glm::vec3 Object::getRotationAxisZLocal() const 
{
    return frame->getRotationAxisZLocal();
}

glm::mat4 Object::getTranslationMatLocal() const 
{
    return frame->getTranslationMatLocal();
}

glm::mat4 Object::getRotationMatLocal() const 
{
    return frame->getRotationMatLocal();
}

glm::mat4 Object::getInverseRotationMatLocal() const 
{
    return frame->getInverseRotationMatLocal();
}

glm::mat4 Object::getScaleMatLocal() const 
{
    return frame->getScaleMatLocal();
}

glm::mat4 Object::getModelMatLocal() const 
{
    return frame->getModelMatLocal();
}

glm::mat4 Object::getInverseModelMatLocal() const 
{
    return frame->getInverseModelMatLocal();
}

glm::vec3 Object::getPositionWorld() const 
{
    return frame->getPositionWorld();
}

glm::quat Object::getRotationWorld() const 
{
    return frame->getRotationWorld();
}

glm::vec3 Object::getScaleWorld() const 
{
    return frame->getScaleWorld();
}

glm::vec3 Object::getRotationAxisXWorld() const 
{
    return frame->getRotationAxisXWorld();
}

glm::vec3 Object::getRotationAxisYWorld() const 
{
    return frame->getRotationAxisYWorld();
}

glm::vec3 Object::getRotationAxisZWorld() const 
{
    return frame->getRotationAxisZWorld();
}

glm::mat4 Object::getTranslationMatWorld() const 
{
    return frame->getTranslationMatWorld();
}

glm::mat4 Object::getRotationMatWorld() const 
{
    return frame->getRotationMatWorld();
}

glm::mat4 Object::getInverseRotationMatWorld() const 
{
    return frame->getInverseRotationMatWorld();
}

glm::mat4 Object::getScaleMatWorld() const 
{
    return frame->getScaleMatWorld();
}

glm::mat4 Object::getModelMatWorld() const 
{
    return frame->getModelMatWorld();
}

glm::mat4 Object::getInverseModelMatWorld() const 
{
    return frame->getInverseModelMatWorld();
}

glm::mat4 Object::getParentModelMatWorld() const 
{
    return frame->getParentModelMatWorld();
}

glm::mat4 Object::getParentInverseModelMatWorld() const 
{
    return frame->getParentInverseModelMatWorld();
}

glm::mat4 Object::getParentRotationMatWorld() const 
{
    return frame->getParentRotationMatWorld();
}

glm::mat4 Object::getParentInverseRotationMatWorld() const 
{
    return frame->getParentInverseRotationMatWorld();
}

void Object::setPosVec(glm::vec3 _position_vec) 
{
    frame->setPosVec(_position_vec);
}

void Object::translatePosVec(glm::vec3 direction) 
{
    frame->translatePosVec(direction);
}

void Object::translatePosVec(glm::mat4 matrix) 
{
    frame->translatePosVec(matrix);
}

void Object::normalizeQuat() 
{
    frame->normalizeQuat();
}

void Object::setRotationQuat(glm::vec3 rotation_vec) 
{
    frame->setRotationQuat(rotation_vec);
}

void Object::setRotationQuat(glm::quat _rotation_quat) 
{
    frame->setRotationQuat(_rotation_quat);
}

void Object::setRotationQuat(const glm::mat4 &rotation_matrix) 
{
    frame->setRotationQuat(rotation_matrix);
}

void Object::rotateRotationQuat(glm::vec3 added_rotation) 
{
    frame->rotateRotationQuat(added_rotation);
}

void Object::rotateRotationQuat(glm::quat added_rotation) 
{
    frame->rotateRotationQuat(added_rotation);
}

void Object::setScale(glm::vec3 _scale_vec) 
{
    frame->setScale(_scale_vec);
}

void Object::setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec) 
{
    frame->setFrame(_position_vec, rotation_vec, _scale_vec);
}

void Object::setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec) 
{
    frame->setFrame(_position_vec, _rotation_quat, _scale_vec);
}

void Object::translatePosVecWorld(glm::vec3 direction) 
{
    frame->translatePosVecWorld(direction);
}

bool Object::isParentOf(frame_ptr other_node) 
{
    return frame->isParentOf(other_node);
}

frame_weak_ptr Object::getRootParent() 
{
    return frame->getRootParent();
}

frame_weak_ptr Object::getParent() const 
{
    return frame->getParent();
}

std::vector<frame_ptr> &Object::getChildren() 
{
    return frame->getChildren();
}

void Object::addChild(frame_ptr child, bool keep_world_transform) 
{
    frame->addChild(child, keep_world_transform);
}

void Object::removeChild(frame_ptr child) 
{
    frame->removeChild(child);
}

void Object::setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform) 
{
    frame->setChildren(_children, keep_world_transform);
}

void Object::removeChildren(const std::vector<frame_ptr> &unwanted_children) 
{
    frame->removeChildren(unwanted_children);
}

void Object::clearChildren() 
{
    frame->clearChildren();
}

void Object::extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform) 
{
    frame->extendChildren(extra_children, keep_world_transform);
}

void Object::transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform) 
{
    frame->transferChild(child, new_parent, keep_world_transform);
}
