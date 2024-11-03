#ifndef TEXTURE_LOAD_INCLUDE
#define TEXTURE_LOAD_INCLUDE

#include <graphics/texture.hpp>

#include <array>
#include <filesystem>

/**
 * Loads a 2D texture from a file. Expect the texture is NOT flipped vertically (bottom-down).
 * Implicitly generates mipmaps and sets the filtering to linear.
 */
GLuint load_texture_2d(const std::filesystem::path filename);

/**
 * Loads a cube map texture from the given files.
 * The order is: +X, -X, +Y, -Y, +Z, -Z (right, left, top, bottom, front, back).
 * Implicitly generates mipmaps and sets the filtering to linear.
 */
GLuint load_texture_cube_map(const std::array<std::filesystem::path, 6> &paths);

#endif // TEXTURE_LOAD_INCLUDE
