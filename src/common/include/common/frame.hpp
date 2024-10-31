#ifndef FRAME_INCLUDE
#define FRAME_INCLUDE

#include <util/math.hpp>

#include <memory>
#include <vector>

class Frame;

using frame_ptr = std::shared_ptr<Frame>;
using frame_weak_ptr = std::weak_ptr<Frame>;

class Frame : public std::enable_shared_from_this<Frame>
{
    // Position (x,y,z) in local space
    glm::vec3 position_vec;
    // Rotation in local space
    glm::quat rotation_quat;
    // Scale (x,y,z) in local space
    glm::vec3 scale_vec;
    // Model matrix of `Frame` in absolute world coordinates
    mutable std::unique_ptr<glm::mat4> model_world = nullptr;
    // Children that have their transformation defined relative to this `Frame`
    std::vector<frame_ptr> children;
    // Weak pointer to the parent that defines the local space for this `Frame` 
    frame_weak_ptr parent = std::weak_ptr<Frame>();
    
    /**
     * Constructs `Frame` from the given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param _rotation_vec Rotation (x,y,z) in Euler angles in local space
     * @param _scale_vec Scale (x,y,z) in local space
     */
    Frame(glm::vec3 _position_vec = glm::vec3(0.0f),
          glm::vec3 rotation_vec = glm::vec3(0.0f),
          glm::vec3 _scale_vec = glm::vec3(1.0f));

    /**
     * Constructs `Frame` from the given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param rotation_quat Rotation in local space
     * @param _scale_vec Scale (x,y,z) in local space
     */
    Frame(glm::vec3 _position_vec,
          glm::quat _rotation_quat,
          glm::vec3 _scale_vec = glm::vec3(1.0f));

    /**
     * Constructs `Frame` from a reference of another `Frame`.
     * @param other Other `Frame` instance l-value
     */
    Frame(const Frame &other);

    /**
     * Constructs `Frame` from a reference of another `Frame`.
     * @param other Other `Frame` instance r-value
     */
    Frame(const Frame &&other);

    /**
     * Copies values from another `Frame`
     * @param other Other `Frame` instance l-value
     */
    Frame &operator=(const Frame &other);

    /**
     * Moves values from another `Frame`
     * @param other Other `Frame` instance r-value
     */
    Frame &operator=(const Frame &&other);

    /* HELPER FUNCTIONS */

    /**
     * Extracts position vector from a homogenous matrix.
     * @return Position (x,y,z) from the last column of a matrix
     */
    static glm::vec3 get_position_from_mat(glm::mat4 mat);

    /**
     * Extracts a 3x3 rotation matrix from a homogenous matrix and converts it to a quaternion.
     * @return Quaternion from the first three columns of a matrix
     */
    static glm::quat get_rotation_from_mat(glm::mat4 mat);

    /**
     * Extracts scale vector from a homogenous matrix.
     * @return Scale (x,y,z) from the first three columns of a matrix
     */
    static glm::vec3 get_scale_from_mat(glm::mat4 mat);

    /**
     * Decomposes a model matrix into three out parameters `position`, `rotation`, and `scale`.
     * @param mat Matrix to decompose
     * @param position Out parameter for extracted position
     * @param rotation Out parameter for extracted rotation
     * @param scale Out parameter for extracted scale
     */
    static void decompose_model_mat(const glm::mat4& mat, glm::vec3& position, glm::quat& rotation, glm::vec3& scale);

        /* WORLD MODEL MATRIX SETTERS */

    /**
     * Helper method, creates a std::unique_ptr<glm::mat4> from a given matrix.
     * @param _model_world Model matrix (assumes it is in world space)
     */
    void setModelMatWorld(glm::mat4 _model_world) const;

    /**
     *  Helper method. Sets model matrices of the `Frame` and all its children (recursively) to `nullptr`.
     */
    void invalidateModelMatWorld() const;

    /**
     * Helper method. Removes a child from the children array. Implicitly sets the child's parent to `nullptr`.
     * @param it Iterator pointing to the child to remove
     */
    void removeChild(std::vector<frame_ptr>::iterator it);

    /**
     * Helper method. Sets the parent of the `Frame` instance.
     * @param _parent `Frame` to be set as the new parent
     * @param recalculate_basis If `true`, recalculates the local transformation of the `Frame`
     * to keep its world transformation the same (uses previous parent to get original world transformation)
     */
    void setParent(frame_weak_ptr _parent, bool recalculate_basis);

    /**
     * Helper method. Removes the `Frame`'s parent, sets local transformation to the `Frame`'s 
     * world transformation before parent removal.
     */
    void removeParent();

public:
    ~Frame() = default;
    
    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param _rotation_vec Rotation (x,y,z) in Euler angles in local space
     * @param _scale_vec Scale (x,y,z) in local space
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(glm::vec3 _position_vec = glm::vec3(0.0f), 
                            glm::vec3 rotation_vec = glm::vec3(0.0f),
                            glm::vec3 _scale_vec = glm::vec3(1.0f));

    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param rotation_quat Rotation in local space
     * @param _scale_vec Scale (x,y,z) in local space
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(glm::vec3 _position_vec,
                            glm::quat _rotation_quat,
                            glm::vec3 _scale_vec = glm::vec3(1.0f));

    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from a decomposition of a given matrix.
     * @param matrix Matrix containing desired translation, rotation and scale
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(const glm::mat4 &matrix);

    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from a decomposition of a given matrix.
     * @param matrix Matrix containing desired translation, rotation and scale
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(const glm::mat4 &&matrix);

    /* NOTE: Can be potentially dangerous */
    /**
     * Creates a shallow copy from a `std::shared_ptr<>` of another `Frame`.
     * Shallow copy means the method is NOT recursively called among all children.
     * @param other_frame `Frame` pointer to copy
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr copy_shallow(frame_ptr other_frame);

    /**
     * Creates a deep copy from a `std::shared_ptr<>` of another `Frame`.
     * Deep copy means the method is recursively called among all children.
     * @param other_frame `Frame` pointer to copy
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr copy_deep(frame_ptr other_frame);

    /* GETTERS */
        /* LOCAL */

    /**
     * @return Position (x,y,z) in local space
     */
    glm::vec3 getPositionLocal() const;

    /**
     * @return Rotation in local space
     */
    glm::quat getRotationLocal() const;

    /**
     * @return Scale (x,y,z) in local space
     */
    glm::vec3 getScaleLocal() const;

    /**
     * @return X-axis (first column) of the local rotation matrix
     */
    glm::vec3 getRotationAxisXLocal() const;

    /**
     * @return Y-axis (second column) of the local rotation matrix
     */
    glm::vec3 getRotationAxisYLocal() const;

    /**
     * @return Z-axis (third column) of the local rotation matrix
     */
    glm::vec3 getRotationAxisZLocal() const;

    /**
     * @return Translation matrix in local space
     */
    glm::mat4 getTranslationMatLocal() const;

    /**
     * @return Rotation matrix in local space
     */
    glm::mat4 getRotationMatLocal() const;

    /**
     * @return Inverse rotation matrix in local space
     */
    glm::mat4 getInverseRotationMatLocal() const;

    /**
     * @return Scale matrix in local space
     */
    glm::mat4 getScaleMatLocal() const;

    /**
     * @return Model matrix in local space
     */
    glm::mat4 getModelMatLocal() const;

    /**
     * @return Inverse model matrix in local space
     */
    glm::mat4 getInverseModelMatLocal() const;

        /* WORLD */

    /**
     * @return Position (x,y,z) in world space
     */
    glm::vec3 getPositionWorld() const;

    /**
     * @return Rotation in world space
     */
    glm::quat getRotationWorld() const;

    /**
     * @return Scale (x,y,z) in world space
     */
    glm::vec3 getScaleWorld() const;

    /**
     * @return X-axis (first column) of the world rotation matrix
     */
    glm::vec3 getRotationAxisXWorld() const;

    /**
     * @return Y-axis (second column) of the world rotation matrix
     */
    glm::vec3 getRotationAxisYWorld() const;

    /**
     * @return Z-axis (third column) of the world rotation matrix
     */
    glm::vec3 getRotationAxisZWorld() const;

    /**
     * @return Translation matrix in world space
     */
    glm::mat4 getTranslationMatWorld() const;

    /**
     * @return Rotation matrix in world space
     */
    glm::mat4 getRotationMatWorld() const;

    /**
     * @return Inverse rotation matrix in world space
     */
    glm::mat4 getInverseRotationMatWorld() const;

    /**
     * @return Scale matrix in world space
     */
    glm::mat4 getScaleMatWorld() const;

    /**
     * @return Model matrix in world space
     */
    glm::mat4 getModelMatWorld() const;

    /**
     * @return Inverse model matrix in world space
     */
    glm::mat4 getInverseModelMatWorld() const;

    /**
     * @return Model matrix of the parent `Frame` in world space
     */
    glm::mat4 getParentModelMatWorld() const;

    /**
     * @return Inverse model matrix of the parent `Frame` in world space
     */
    glm::mat4 getParentInverseModelMatWorld() const;

    /**
     * @return Rotation matrix of the parent `Frame` in world space
     */
    glm::mat4 getParentRotationMatWorld() const;

    /**
     * @return Inverse rotation matrix of the parent `Frame` in world space
     */
    glm::mat4 getParentInverseRotationMatWorld() const;

    /* SETTERS */

    /**
     * Sets local position (x,y,z).
     * @param _position_vec Position (x,y,z) in local space
     */

    void setPosVec(glm::vec3 _position_vec);
    /**
     * Translates local position (x,y,z) by a given vector.
     * @param direction Translation vector in `Frame`'s local space
     */
    void translatePosVec(glm::vec3 direction);

    /**
     * Translates local position (x,y,z) by multiplication with a given homogenous matrix.
     * @param matrix Homogenous matrix with translation in the fourth column
     */
    void translatePosVec(glm::mat4 matrix);

    /**
     * Normalizes the local rotation quaternion.
     */
    void normalizeQuat();

    /**
     * Sets local rotation quaternion by constructing it from Euler angles.
     */
    void setRotationQuat(glm::vec3 rotation_vec);

    /**
     * Sets local rotation quaternion.
     */
    void setRotationQuat(glm::quat _rotation_quat);
    
    /**
     * Sets local rotation quaternion by extracting it from a given rotation matrix.
     * @param rotation_matrix Rotation matrix where the first three columns represent the rotation
     */
    void setRotationQuat(const glm::mat4 &rotation_matrix);

    /**
     * Multiplies local rotation quaternion by a quaternion constructed from given Euler angles.
     * @param added_rotation Rotation in Euler angles
     */
    void rotateRotationQuat(glm::vec3 added_rotation);

    /**
     * Multiplies local rotation quaternion by a given quaternion.
     */
    void rotateRotationQuat(glm::quat added_rotation);
    
    /**
     * Sets local scale (x,y,z).
     * @param _scale_vec Scale (x,y,z) in local space
     */
    void setScale(glm::vec3 _scale_vec);

    /**
     * Sets local position, rotation and scale.
     * @param _position_vec Position (x,y,z) in local space
     * @param rotation_vec Rotation (x,y,z) in Euler angles in local space
     * @param _scale_vec Scale (x,y,z) in local space
     */
    void setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec);

    /**
     * Sets local position, rotation and scale.
     * @param _position_vec Position (x,y,z) in local space
     * @param _rotation_quat Rotation in local space
     * @param _scale_vec Scale (x,y,z) in local space
     */
    void setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec);

    /**
     * Translates `Frame` so that its world position changes by a vector given in world space.
     * @param direction Translation vector in world space 
     */
    void translatePosVecWorld(glm::vec3 direction);

    /* FRAME HIERARCHY METHODS */

    /**
     * @param other_node Potential direct child of this `Frame` instance 
     * @return `true` if this `Frame` instance is a direct parent of another `Frame`, `false` otherwise
     */
    bool isParentOf(frame_ptr other_node);

    /**
     * @return Pointer to the root parent of this `Frame` instance,
     * if the `Frame` has no parent, returns itself.
     */
    frame_weak_ptr getRootParent();

    /**
     * @return Pointer to the direct parent of this `Frame` instance
     */
    frame_weak_ptr getParent() const;

    /**
     * @return Reference to the children array of this `Frame` instance
     */
    std::vector<frame_ptr> &getChildren();

    /**
     * Adds given `Frame` as a child of this `Frame`, implicitly sets the child's parent.
     * @param child `Frame` instance to add as a child
     * @param keep_world_transform If `true`, the child's world transformation is preserved 
     * (local transformation is recalculated) 
     */
    void addChild(frame_ptr child, bool keep_world_transform = true);

    /**
     * If the children array contains `child` it is removed from said array. 
     * Implicitly sets the child's parent to `nullptr` even if the child is not in the array.
     * NOTE: Might want to change the behavior to not set the parent 
     *       to `nullptr` if the child is not in the array.
     * @param child Child `Frame` to remove
     */
    void removeChild(frame_ptr child);

    /**
     * Sets the children array, erasing all previous children (`removeChild()` is called for each of them).
     * @param _children New children array
     * @param keep_world_transform If `true`, the children's world transformation is preserved
     */
    void setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform = true);

    /**
     * Removes a subset of children. The `removeChild()` method is called implicitly for each child
     * in `unwanted_children`.
     * @param unwanted_children Children to remove
     */
    void removeChildren(const std::vector<frame_ptr> &unwanted_children);

    /**
     * Removes all children from the children array. 
     * The `removeChild()` method is called implicitly for each child.
     */
    void clearChildren();

    /**
     * Adds children from the `extra_children` array to the children array. Calls `addChild()` implicitly.
     * @param extra_children Array of children to add
     * @param keep_world_transform If `true`, the children's world transformation is preserved
     */
    void extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform = true);

    /**
     * Transfers a child from this `Frame` to another parent. 
     * Does not check if the child is actually a child of this `Frame`.
     * NOTE: This could be a static method.
     * @param child Child `Frame` to transfer
     * @param new_parent New parent `Frame` to transfer the child to
     * @param keep_world_transform If `true`, the child's world transformation is preserved
     */
    void transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform = true);
};

#endif // FRAME_INCLUDE
