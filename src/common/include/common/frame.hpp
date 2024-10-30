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
    Frame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec);

    /**
     * Constructs `Frame` from the given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param rotation_quat Rotation in local space
     * @param _scale_vec Scale (x,y,z) in local space
     */
    Frame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec);

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

public:
    ~Frame() = default;
    
    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param _rotation_vec Rotation (x,y,z) in Euler angles in local space
     * @param _scale_vec Scale (x,y,z) in local space
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(glm::vec3 _position_vec, 
                            glm::vec3 rotation_vec,
                            glm::vec3 _scale_vec);

    /**
     * Static method. Creates a `std::shared_ptr<Frame>` from given parameters.
     * @param _position_vec Position (x,y,z) in local space
     * @param rotation_quat Rotation in local space
     * @param _scale_vec Scale (x,y,z) in local space
     * @return Shared pointer to a `Frame`
     */
    static frame_ptr create(glm::vec3 _position_vec,
                            glm::quat _rotation_quat,
                            glm::vec3 _scale_vec);

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
     * 
     */
    glm::vec3 getPositionLocal() const;
    glm::quat getRotationLocal() const;
    glm::vec3 getScaleLocal() const;

    glm::vec3 getRotationAxisXLocal() const;
    glm::vec3 getRotationAxisYLocal() const;
    glm::vec3 getRotationAxisZLocal() const;

    glm::mat4 getTranslationMatLocal() const;
    glm::mat4 getRotationMatLocal() const;
    glm::mat4 getInverseRotationMatLocal() const;
    glm::mat4 getScaleMatLocal() const;

    glm::mat4 getModelMatLocal() const;
    glm::mat4 getInverseModelMatLocal() const;

        /* WORLD */
    glm::vec3 getPositionWorld() const;
    glm::quat getRotationWorld() const;
    glm::vec3 getScaleWorld() const;

    glm::vec3 getRotationAxisXWorld() const;
    glm::vec3 getRotationAxisYWorld() const;
    glm::vec3 getRotationAxisZWorld() const;

    glm::mat4 getTranslationMatWorld() const;
    glm::mat4 getRotationMatWorld() const;
    glm::mat4 getInverseRotationMatWorld() const;
    glm::mat4 getScaleMatWorld() const;

    glm::mat4 getModelMatWorld() const;
    glm::mat4 getInverseModelMatWorld() const;

    glm::mat4 getParentModelMatWorld() const;
    glm::mat4 getParentInverseModelMatWorld() const;
    glm::mat4 getParentRotationMatWorld() const;
    glm::mat4 getParentInverseRotationMatWorld() const;

    /* SETTERS */

    void setPosVec(glm::vec3 _position_vec);
    void translatePosVec(glm::vec3 direction);
    void translatePosVec(glm::mat4 matrix);
    void setRotationQuat(glm::vec3 rotation_vec);
    void setRotationQuat(glm::quat _rotation_quat);
    void setRotationQuat(const glm::mat4 &rotation_matrix);
    void rotateRotationQuat(glm::vec3 added_rotation);
    void rotateRotationQuat(glm::quat added_rotation);
    void setScale(glm::vec3 _scale_vec);

    void setFrame(glm::vec3 _position_vec, glm::vec3 rotation_vec, glm::vec3 _scale_vec);
    void setFrame(glm::vec3 _position_vec, glm::quat _rotation_quat, glm::vec3 _scale_vec);

    void translatePosVecWorld(glm::vec3 direction);

    void normalizeQuat();

    /* WORLD MODEL MATRIX SETTERS */

    void setModelMatWorld(glm::mat4 _model_world) const;
    void invalidateModelMatWorld() const;

    /* FRAME HIERARCHY METHODS */

    bool isParentOf(frame_ptr other_node);
    frame_weak_ptr getRootParent();
    frame_weak_ptr getParent() const;

    std::vector<frame_ptr> &getChildren();
    void addChild(frame_ptr child, bool keep_world_transform = true);
    void removeChild(std::vector<frame_ptr>::iterator it);
    void removeChild(frame_ptr child);
    void setChildren(std::vector<frame_ptr> &_children, bool keep_world_transform = true);
    void removeChildren(const std::vector<frame_ptr> &unwanted_children);
    void clearChildren();
    void extendChildren(const std::vector<frame_ptr> &extra_children, bool keep_world_transform = true);

    void transferChild(frame_ptr child, frame_weak_ptr new_parent, bool keep_world_transform = true);

protected:

    void setParent(frame_weak_ptr _parent, bool recalculate_basis);
    void removeParent();
};

#endif // FRAME_INCLUDE
