#include <common/frame.hpp>

#include <util/assumption.hpp>

#include <algorithm>
#include <iterator>

/* PROTECTED */
Frame::Frame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec)
: position_vec{_position_vec}
, scale_vec{_scale_vec}
{    
    setRotationQuat(rotation_vec);
}

Frame::Frame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec)
: position_vec{_position_vec}
, rotation_quat{glm::normalize(_rotation_quat)}
, scale_vec(_scale_vec) 
{}

Frame::Frame(const Frame &other)
{
    position_vec = other.position_vec;
    rotation_quat = other.rotation_quat;
    scale_vec = other.scale_vec;
    model_world = other.model_world == nullptr ? nullptr : std::make_unique<glm::mat4>(*other.model_world);
}

Frame::Frame(const Frame &&other)
{
    position_vec = other.position_vec;
    rotation_quat = other.rotation_quat;
    scale_vec = other.scale_vec;
    model_world = std::move(other.model_world);
}

Frame& Frame::operator=(const Frame &other)
{
    position_vec = other.position_vec;
    rotation_quat = other.rotation_quat;
    scale_vec = other.scale_vec;
    model_world = other.model_world == nullptr ? nullptr : std::make_unique<glm::mat4>(*other.model_world);

    return *this;
}

Frame& Frame::operator=(const Frame &&other)
{
    position_vec = other.position_vec;
    rotation_quat = other.rotation_quat;
    scale_vec = other.scale_vec;
    model_world = std::move(other.model_world);

    return *this;
}

glm::vec3 Frame::get_position_from_mat(glm::mat4 mat)
{ 
    return mat[3]; 
}

glm::quat Frame::get_rotation_from_mat(glm::mat4 mat)
{
    auto scale = get_scale_from_mat(mat);
    const glm::mat3 rotation_mat(
        glm::vec3(mat[0]) / scale[0],
        glm::vec3(mat[1]) / scale[1],
        glm::vec3(mat[2]) / scale[2]);
    return glm::quat_cast(rotation_mat);
}

glm::vec3 Frame::get_scale_from_mat(glm::mat4 mat)
{ 
    glm::vec3 scale;
    for (int i = 0; i < 3; ++i)
        scale[i] = glm::length(glm::vec3(mat[i]));
    return scale;
}

void Frame::decompose_model_mat(const glm::mat4& mat, glm::vec3& position, glm::quat& rotation, glm::vec3& scale)
{
    position = mat[3];
    for(int i = 0; i < 3; ++i)
        scale[i] = glm::length(glm::vec3(mat[i]));

    const glm::mat3 rotation_mat(
        glm::vec3(mat[0]) / scale[0],
        glm::vec3(mat[1]) / scale[1],
        glm::vec3(mat[2]) / scale[2]);
    rotation = glm::quat_cast(rotation_mat);
}

/* PUBLIC */
frame_ptr Frame::create(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec)
{
    return frame_ptr{ new Frame(_position_vec, rotation_vec, _scale_vec) };
}

frame_ptr Frame::create(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec)
{
    return frame_ptr{ new Frame(_position_vec, _rotation_quat, _scale_vec) };
}

frame_ptr Frame::create(const glm::mat4 &matrix)
{
    glm::vec3 position;
    glm::quat rotation; 
    glm::vec3 scale;
    decompose_model_mat(matrix, position, rotation, scale);

    return Frame::create(position, rotation, scale);
}

frame_ptr Frame::create(const glm::mat4 &&matrix)
{
    glm::vec3 position;
    glm::quat rotation; 
    glm::vec3 scale;
    decompose_model_mat(matrix, position, rotation, scale);
    
    return Frame::create(position, rotation, scale);
}

frame_ptr Frame::copy_shallow(frame_ptr other_frame)
{
    auto frame = frame_ptr{ new Frame(*other_frame) };

    frame->setChildren(other_frame->getChildren());

    return frame;
}

frame_ptr Frame::copy_deep(frame_ptr other_frame)
{
    auto frame = frame_ptr{ new Frame(*other_frame) };
       
    for (auto &child : other_frame->getChildren())
        frame->addChild(Frame::copy_deep(child));

    return frame;
}

/* GETTERS */
    /* LOCAL */
glm::vec3 Frame::getPositionLocal() const { return position_vec; }

glm::quat Frame::getRotationLocal() const { return rotation_quat; }

glm::vec3 Frame::getScaleLocal() const { return scale_vec; }

glm::vec3 Frame::getRotationAxisXLocal() const { return glm::normalize(glm::column(glm::toMat3(rotation_quat), 0)); }

glm::vec3 Frame::getRotationAxisYLocal() const { return glm::normalize(glm::column(glm::toMat3(rotation_quat), 1)); }

glm::vec3 Frame::getRotationAxisZLocal() const { return glm::normalize(glm::column(glm::toMat3(rotation_quat), 2)); }

glm::mat4 Frame::getTranslationMatLocal() const { return glm::translate(glm::mat4(1.0f), position_vec); }

glm::mat4 Frame::getRotationMatLocal() const { return glm::toMat4(rotation_quat); }

glm::mat4 Frame::getInverseRotationMatLocal() const { return glm::inverse(getRotationMatLocal()); }

glm::mat4 Frame::getScaleMatLocal() const { return glm::scale(glm::mat4(1.0f), scale_vec); }

glm::mat4 Frame::getModelMatLocal() const { return getTranslationMatLocal() * getRotationMatLocal() * getScaleMatLocal(); }

glm::mat4 Frame::getInverseModelMatLocal() const { return glm::inverse(getModelMatLocal()); }

    /* WORLD */
glm::vec3 Frame::getPositionWorld() const { return get_position_from_mat(getModelMatWorld()); }

glm::quat Frame::getRotationWorld() const { return get_rotation_from_mat(getModelMatWorld()); }

glm::vec3 Frame::getScaleWorld() const { return get_scale_from_mat(getModelMatWorld()); }

glm::vec3 Frame::getRotationAxisXWorld() const { return glm::normalize(glm::column(glm::toMat3(getRotationWorld()), 0)); }

glm::vec3 Frame::getRotationAxisYWorld() const { return glm::normalize(glm::column(glm::toMat3(getRotationWorld()), 1)); }

glm::vec3 Frame::getRotationAxisZWorld() const { return glm::normalize(glm::column(glm::toMat3(getRotationWorld()), 2)); }

glm::mat4 Frame::getTranslationMatWorld() const { return glm::translate(glm::mat4(1.0f), get_position_from_mat(getModelMatWorld())); }

glm::mat4 Frame::getRotationMatWorld() const { return glm::toMat4(get_rotation_from_mat(getModelMatWorld())); }

glm::mat4 Frame::getInverseRotationMatWorld() const { return glm::inverse(getRotationMatWorld()); }

glm::mat4 Frame::getScaleMatWorld() const { return glm::scale(glm::mat4(1.0f), get_scale_from_mat(getModelMatWorld())); }

glm::mat4 Frame::getModelMatWorld() const 
{
    if (!model_world)
    {
        if (parent.expired())
            setModelMatWorld(getModelMatLocal());
        else
            setModelMatWorld(parent.lock()->getModelMatWorld() * getModelMatLocal());

        return *model_world;
    }

    return *model_world;
}

glm::mat4 Frame::getInverseModelMatWorld() const { return glm::inverse(getModelMatWorld()); }

glm::mat4 Frame::getParentModelMatWorld() const { return !parent.expired() ? parent.lock()->getModelMatWorld() : glm::mat4(1.0f); }

glm::mat4 Frame::getParentInverseModelMatWorld() const { return !parent.expired() ? parent.lock()->getRotationMatWorld() : glm::mat4(1.0f); }

glm::mat4 Frame::getParentRotationMatWorld() const { return  !parent.expired() ? parent.lock()->getInverseModelMatWorld() : glm::mat4(1.0f); }

glm::mat4 Frame::getParentInverseRotationMatWorld() const { return  !parent.expired() ? parent.lock()->getInverseRotationMatWorld() : glm::mat4(1.0f); }

/* SETTERS */
    /* LOCAL */
void Frame::setPosVec(glm::vec3 _position_vec) 
{ 
    position_vec = _position_vec; 
    invalidateModelMatWorld(); 
}

void Frame::translatePosVec(glm::vec3 direction) 
{ 
    position_vec += direction; 
    invalidateModelMatWorld(); 
}

void Frame::translatePosVec(glm::mat4 matrix)
{
    position_vec = matrix * glm::vec4(position_vec, 1.0f);
    invalidateModelMatWorld();
}

void Frame::normalizeQuat() { rotation_quat = glm::normalize(rotation_quat); }

void Frame::setRotationQuat(glm::vec3 rotation_vec) 
{ 
    rotation_quat = glm::normalize(glm::tquat(glm::radians(rotation_vec))); 
    invalidateModelMatWorld(); 
}

void Frame::setRotationQuat(glm::quat _rotation_quat) 
{ 
    rotation_quat = glm::normalize(_rotation_quat); 
    invalidateModelMatWorld();
}

void Frame::setRotationQuat(const glm::mat4 &rotation_matrix)
{
    rotation_quat = get_rotation_from_mat(rotation_matrix);
    invalidateModelMatWorld();
}

void Frame::rotateRotationQuat(glm::vec3 added_rotation) 
{ 
    rotation_quat = glm::normalize(glm::tquat(glm::radians(added_rotation)) * rotation_quat); 
    invalidateModelMatWorld(); 
}

void Frame::rotateRotationQuat(glm::quat added_rotation) 
{ 
    rotation_quat = glm::normalize(added_rotation * rotation_quat); 
    invalidateModelMatWorld(); 
}

void Frame::setScale(glm::vec3 _scale_vec) 
{ 
    scale_vec = _scale_vec; 
    invalidateModelMatWorld(); 
}

void Frame::setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec)
{
    setPosVec(_position_vec);
    setRotationQuat(rotation_vec);
    setScale(_scale_vec);
    invalidateModelMatWorld();
}

void Frame::setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec)
{
    setPosVec(_position_vec);
    setRotationQuat(_rotation_quat);
    setScale(_scale_vec);
    invalidateModelMatWorld();
}

    /* WORLD */
void Frame::translatePosVecWorld(glm::vec3 direction) 
{ 
    position_vec += glm::vec3(getParentInverseModelMatWorld() * glm::vec4(direction, 0.0f)); 
    invalidateModelMatWorld(); 
}

/* WORLD MODEL MATRIX SETTERS */
void Frame::setModelMatWorld(glm::mat4 _model_world) const { model_world = std::make_unique<glm::mat4>(_model_world); }

void Frame::invalidateModelMatWorld() const 
{ 
    for (auto &child : children)
        child->invalidateModelMatWorld();

    model_world = nullptr;
}

/* NODE HIERARCHY METHODS */
bool Frame::isParentOf(frame_ptr other_frame)
{
    for (auto &child : children)
    {
        if (child == other_frame)
            return true;
        if (child->isParentOf(other_frame))
            return true;
    }

    return false;
}

frame_weak_ptr Frame::getRootParent()
{
    if (parent.expired())
        return weak_from_this();
    return parent.lock()->getRootParent();
}

frame_weak_ptr Frame::getParent() const { return parent; }

std::vector<frame_ptr> &Frame::getChildren() { return children; }

void Frame::addChild(frame_ptr child, bool keep_world_transform) 
{
    child->setParent(weak_from_this(), keep_world_transform);
    children.emplace_back(child); 
}

void Frame::removeChild(std::vector<frame_ptr>::iterator it)
{
    it.operator*()->removeParent();
    children.erase(it);
}

void Frame::removeChild(frame_ptr child) 
{
    removeChild(std::find(children.begin(), children.end(), child));
}

void Frame::setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform)
{ 
    clearChildren();
    extendChildren(_children, keep_world_transform);
}

void Frame::removeChildren(const std::vector<frame_ptr> &unwanted_children)
{
    for (const auto &unwanted_child : unwanted_children)
        if (auto it = std::find(children.begin(), children.end(), unwanted_child);
            it != children.end())
            removeChild(it);
}

void Frame::clearChildren()
{
    for (auto it = children.begin(); it != children.end(); it = children.begin())
        removeChild(it);
}

void Frame::extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform)
{
    for (auto &child : extra_children)
        addChild(child, keep_world_transform);
}

void Frame::transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform)
{
    children.erase(std::find(children.begin(), children.end(), child));
    new_parent.lock()->addChild(child, keep_world_transform);
}

/* PROTECTED */

void Frame::setParent(frame_weak_ptr _parent, bool recalculate_basis) 
{
    // Tranforms child to parent's base. The child keeps its world position, rotation and scale this way
    if (recalculate_basis && !_parent.expired())
    {
        glm::vec3 position;
        glm::quat rotation; 
        glm::vec3 scale;
        decompose_model_mat(_parent.lock()->getInverseModelMatWorld() * getModelMatLocal(), position, rotation, scale);
        
        setPosVec(position);
        setRotationQuat(rotation);
        setScale(scale);
    }

    parent = _parent; 
    invalidateModelMatWorld();
}

void Frame::removeParent() 
{
    glm::vec3 position;
    glm::quat rotation; 
    glm::vec3 scale;
    decompose_model_mat(getModelMatWorld(), position, rotation, scale);
    
    setPosVec(position);
    setRotationQuat(rotation);
    setScale(scale);

    parent.reset(); 
    invalidateModelMatWorld();
}
