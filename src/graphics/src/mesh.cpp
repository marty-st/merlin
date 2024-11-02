#include <graphics/mesh.hpp>

Mesh::Mesh(std::vector<float> const &_vertices,
           std::vector<float> const &_normals,
           std::vector<unsigned int> const &_indices,
           std::vector<float> const &_texture_coordinates)
{
    _VAO = std::make_unique<VAO>();
    _VAO->bindBuffers(_vertices, _normals, _indices, _texture_coordinates);
}

const VAO* Mesh::getVAO() const
{
    return _VAO.get();
}

const GLenum Mesh::getDrawMode() const
{
    return draw_mode;
}

void Mesh::setDrawMode(GLenum mode)
{
    draw_mode = mode;
}

// mesh_ptr Mesh::loadMesh(const std::filesystem::path &obj_file, const std::filesystem::path texture_file)
// {
//     // mesh_ptr mesh = load_object(obj_file);
//     // if (texture_file != "")
//     //     mesh->texture = Texture::loadTexture(texture_file);

//     // return mesh;
// }

// mesh_ptr Mesh::loadMesh(const std::filesystem::path &obj_file, bool normalize, bool centralize, const std::filesystem::path texture_file)
// {
//     // mesh_ptr mesh = load_object(obj_file, normalize, centralize);
//     // if (texture_file != "")
//     //     mesh->texture = Texture::loadTexture(texture_file);

//     // return mesh;
// }

// mesh_ptr Mesh::loadMesh(const std::filesystem::path &obj_file, const std::vector<std::filesystem::path> &cubemap_texture_files)
// {
//     // mesh_ptr mesh = load_object(obj_file);
//     // mesh->texture = Texture::loadTexture(cubemap_texture_files);

//     // return mesh;
// }
