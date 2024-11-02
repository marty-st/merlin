#ifndef GRAPHICAL_OBJECT_INCLUDE
#define GRAPHICAL_OBJECT_INCLUDE

#include <common/object.hpp>
#include <graphics/mesh.hpp>
#include <graphics/material.hpp>
#include <graphics/texture.hpp>

#include <memory>
#include <unordered_map>

using material_ptr = std::shared_ptr<Material>;

enum class TextureUsage
{
    ALBEDO,
    NORMAL,
    DEBUG,
    // METALLIC,
    // ROUGHNESS,
    // AMBIENT_OCCLUSION
};

/**
 * Derived from `Object`. Represents a graphical object rendered in the scene. 
 */
class GraphicalObject : public Object
{
protected:
    // Mesh
    mesh_ptr mesh = nullptr;
    // Material
    material_ptr material = nullptr;
    // Textures
    std::unordered_map<TextureUsage, texture_ptr> textures;

    // TO DO:
    //Shader

    // TO DO:
    // Bounding box - Compute AABB before sending data to create Mesh object, 
    // maybe when calling loadMesh, call it in a another method here that return the bbox

public:
    GraphicalObject(frame_ptr _frame, 
                    mesh_ptr _mesh, 
                    material_ptr _material = nullptr, 
                    std::unordered_map<TextureUsage, texture_ptr> textures = {} //, shader_ptr shader
    );

    /**
     * @return Shared pointer to the underlying `Mesh`
     */
    mesh_ptr getMesh() const;

    /**
     * Sets the mesh of the graphical object.
     * @param _mesh Shared pointer to a `Mesh`
     */
    void setMesh(mesh_ptr _mesh);

    /**
     * @return Shared pointer to object's `Material`
     */
    material_ptr getMaterial() const;

    /**
     * Sets the material of the graphical object.
     * @param _material Shared pointer to a `Material`
     */
    void setMaterial(material_ptr _material);

    /**
     * @return Vector of shared pointers to the object's textures
     */
    const std::unordered_map<TextureUsage, texture_ptr> &getTextures() const;

    /**
     * Sets an albedo texture to the graphical object.
     * @param texture Shared pointer to a `Texture`
     */
    void setTextureAlbedo(texture_ptr texture);

    /**
     * Sets a normal texture to the graphical object.
     * @param texture Shared pointer to a `Texture`
     */
    void setTextureNormal(texture_ptr texture);

    /**
     * Sets a texture used for debug purposes to the graphical object.
     * @param texture Shared pointer to a `Texture`
     */
    void setTextureDebug(texture_ptr texture);

    /**
     * Sets a given texture to be used according to provided `TextureUsage`.
     * @param usage Type of the texture
     * @param texture Shared pointer to a `Texture`
     */
    void setTexture(TextureUsage usage, texture_ptr texture);

    /**
     * Removes a texture from the graphical object.
     * @param texture Shared pointer to a `Texture`
     */
    void removeTexture(TextureUsage usage);

    /**
     * Sets the textures of the graphical object.
     * @param textures Map of `TextureUsage` to shared pointers to `Texture`
     */
    void setTextures(const std::unordered_map<TextureUsage, texture_ptr> &_textures);

    /**
     * Calls OpenGL's `glDraw*` to render the graphical object.
     * NOTE: Even though it seems that this functionality should be managed by `Mesh`,
     * it doesn't make sense from a design perspective to be able to use the `Mesh` 
     * class to draw on its own.
     */
    void draw() const;
};

using GObject = GraphicalObject;

#endif // GRAPHICAL_OBJECT_INCLUDE
