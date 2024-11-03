#include <graphics/texture.hpp>

#include <file/texture_load.hpp>

Texture::Texture(GLuint _ID, TextureType _type)
: ID{_ID} 
, type{_type}
{}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

const GLuint Texture::getID() const
{
    return ID;
}

const TextureType Texture::getType() const
{
    return type;
}

texture_ptr Texture::createTexture2D(const std::filesystem::path texture_file)
{
    auto texture = load_texture_2d(texture_file);
    if (!texture)
    {
        return nullptr;
    }

    return texture_ptr{ new Texture(texture, TextureType::T2D) };
}

texture_ptr Texture::createTextureCube(const std::array<std::filesystem::path, 6> &cube_texture_files)
{
    auto texture = load_texture_cube_map(cube_texture_files);
    if (!texture)
    {
        return nullptr;
    }

    return texture_ptr{ new Texture(texture, TextureType::CUBE) };
}
