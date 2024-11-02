#include <graphics/graphical_object.hpp>

GraphicalObject::GraphicalObject(frame_ptr _frame, 
                mesh_ptr _mesh, 
                material_ptr _material, 
                std::unordered_map<TextureUsage, texture_ptr> textures //, shader_ptr shader
    )
: Object{_frame}
, mesh{_mesh}
, material{_material}
, textures{textures}
{}

mesh_ptr GraphicalObject::getMesh() const
{
    return mesh;
}

void GraphicalObject::setMesh(mesh_ptr _mesh)
{
    mesh = _mesh;
}

material_ptr GraphicalObject::getMaterial() const
{
    return material;
}

void GraphicalObject::setMaterial(material_ptr _material)
{
    material = _material;
}

const std::unordered_map<TextureUsage, texture_ptr> &GraphicalObject::getTextures() const
{
    return textures;
}

void GraphicalObject::setTextureAlbedo(texture_ptr texture)
{
    textures[TextureUsage::ALBEDO] = texture;
}

void GraphicalObject::setTextureNormal(texture_ptr texture)
{
    textures[TextureUsage::NORMAL] = texture;
}

void GraphicalObject::setTextureDebug(texture_ptr texture)
{
    textures[TextureUsage::DEBUG] = texture;
}

void GraphicalObject::setTexture(TextureUsage usage, texture_ptr texture)
{
    textures[usage] = texture;
}

void GraphicalObject::removeTexture(TextureUsage usage)
{
    textures.erase(usage);
}

void GraphicalObject::setTextures(const std::unordered_map<TextureUsage, texture_ptr> &_textures)
{
    textures = _textures;
}

void GraphicalObject::draw() const
{
    auto VAO = mesh->getVAO();
    VAO->bind();

    if (VAO->getIndicesSize() == 0)
    {
        glDrawArrays(mesh->getDrawMode(),
                     0,
                     static_cast<GLsizei>(VAO->getVerticesSize()));
        ASSUME(glGetError() == GL_NO_ERROR);
        
    }
    else
    {
        glDrawElements(mesh->getDrawMode(),
                       static_cast<GLsizei>(VAO->getIndicesSize()),
                       GL_UNSIGNED_INT, 
                       0);
        ASSUME(glGetError() == GL_NO_ERROR);
    }
}
