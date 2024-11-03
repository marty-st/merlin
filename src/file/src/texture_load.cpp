#include <file/texture_load.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <osi/stb_image.h>

#define STBI_FAILURE_USERMSG

#include <osi/opengl.hpp>
#include <util/assumption.hpp>

#include <iostream>
#include <string>

GLenum get_texture_format(const int channels)
{
    switch (channels)
    {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        return GL_RGBA;
    }
}

void handle_load_failure(unsigned char* data, const std::filesystem::path &filename, std::string_view msg)
{
    std::cerr << msg << ": " << filename << std::endl;
    stbi_failure_reason();
    stbi_image_free(data);
}

GLuint load_texture_2d(const std::filesystem::path filename) 
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* data = stbi_load(filename.generic_string().data(), &width, &height, &channels, 0);

    if (!data)
    {
        handle_load_failure(data, filename, "Unsupported texture format");
        return 0;
    }

    GLuint texture;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);

    GLenum format = get_texture_format(channels);

    glTextureStorage2D(texture, static_cast<GLsizei>(std::log2(width)), format, width, height);

    glTextureSubImage2D(texture,
                        0,                         //
                        0, 0,                      //
                        width, height,             //
                        format, GL_UNSIGNED_BYTE,  //
                        data);

    stbi_image_free(data);

    glGenerateTextureMipmap(texture);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

GLuint load_texture_cube_map(const std::array<std::filesystem::path, 6> &paths)
{
    stbi_set_flip_vertically_on_load(false);

    int ok, width, height, channels;

    ok = stbi_info(paths[0].generic_string().data(), &width, &height, &channels);
    if (!ok)
    {
        handle_load_failure(nullptr, paths[0], "Failed to load texture");
        return 0;
    }

    unsigned char* data = stbi_load(paths[0].generic_string().data(), &width, &height, &channels, 0);
    ASSUME(width == height);

    GLuint texture;
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &texture);

    glTextureStorage2D(texture, static_cast<GLsizei>(std::log2(width)) + 1, GL_RGBA8, width, height);

    assert(paths.size() == 6);
    for (unsigned int i = 0; i < paths.size(); ++i)
    {
        int width, height, channels;
        unsigned char* data = stbi_load(paths[i].generic_string().data(), &width, &height, &channels, 0);
        if (data)
        {
            GLenum format = get_texture_format(channels);
            glTextureSubImage3D(texture,
                                0, // Mipmap level
                                0, 0, i, // (x, y, face) offset
                                width, height, 1, // (w, h, depth)
                                format,
                                GL_UNSIGNED_BYTE,
                                data);

            stbi_image_free(data);
        }
        else
        {
            handle_load_failure(data, paths[i], "Failed to load texture");
        }
    }
    glGenerateTextureMipmap(texture);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texture;
}
