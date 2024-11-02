#ifndef MESH_INCLUDE
#define MESH_INCLUDE

#include <graphics/vao.hpp>

#include <filesystem>
#include <memory>

using VAO_ptr = std::unique_ptr<VAO>;

class Mesh;
// Shared pointer to a mesh object. Makes sense to share same geometry.
using mesh_ptr = std::shared_ptr<Mesh>;

/**
 * Wrapper for mesh related data. Manages the VAO and draw mode.
 */
class Mesh
{
    VAO_ptr _VAO = nullptr;
    GLenum draw_mode = GL_TRIANGLES;

public:
    /**
     * Creates a new mesh with the given data. Requires at least vertices and normals.
     * @param _vertices Vector of vertex data
     * @param _normals Vector of normal data
     * @param _indices Vector of index data
     * @param _texture_coordinates Vector of texture coordinate data
     */
    Mesh(std::vector<float> const &_vertices,
         std::vector<float> const &_normals,
         std::vector<unsigned int> const &_indices = {},
         std::vector<float> const &_texture_coordinates = {});

    /**
     * @return Raw pointer to the VAO. Used to bind the VAO for rendering.
     */
    const VAO* getVAO() const;

    /**
     * @return Mode used by OpenGL during the draw call.
     */
    const GLenum getDrawMode() const;

    /**
     * Sets the draw mode of the mesh.
     * @param mode New draw mode
     */
    void setDrawMode(GLenum mode);

    // static mesh_ptr loadMesh(const std::filesystem::path &obj_file, const std::filesystem::path texture_file = "");
    // static mesh_ptr loadMesh(const std::filesystem::path &obj_file, bool normalize, bool centralize, const std::filesystem::path texture_file = "");
    // static mesh_ptr loadMesh(const std::filesystem::path &obj_file, const std::vector<std::filesystem::path> &cubemap_texture_files);
};

#endif // MESH_INCLUDE
