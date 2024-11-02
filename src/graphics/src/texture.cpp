#include <graphics/texture.hpp>

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

// texture_ptr Texture::loadTexture(const std::filesystem::path texture_file)
// {
//     // return load_texture_2d(texture_file);
// }

// texture_ptr Texture::loadCubeTexture(const std::array<std::filesystem::path, 6> &cube_texture_files)
// {
//     // return load_texture_cube(cube_texture_files);
// }

// texture_ptr load_texture_2d(const std::filesystem::path filename, TextureUsage usage) 
// {
//     stbi_set_flip_vertically_on_load(true);

//     int width, height, channels;
//     unsigned char* data = stbi_load(filename.generic_string().data(), &width, &height, &channels, 4);

//     if (!data)
//     {
//         std::cerr << "Failed to load texture: " << texture_file << std::endl;
//         stbi_image_free(data);
//         return nullptr;
//     }

//     GLuint texture;
//     glCreateTextures(GL_TEXTURE_2D, 1, &texture);

//     GLenum format;
//     if (channels == 1)
//         format = GL_RED;
//     else if (channels == 3)
//         format = GL_RGB8;
//     else if (channels == 4)
//         format = GL_RGBA8;

//     glTextureStorage2D(texture, static_cast<GLsizei>(std::log2(width)), format, width, height);

//     glTextureSubImage2D(texture,
//                         0,                         //
//                         0, 0,                      //
//                         width, height,             //
//                         format, GL_UNSIGNED_BYTE, //
//                         data);

//     stbi_image_free(data);

//     glGenerateTextureMipmap(texture);

//     glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     return std::make_shared<Texture>(texture, TextureType::T2D, TextureUsage::ALBEDO);
// }
