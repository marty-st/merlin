#include <graphics/vao.hpp>

#include <util/assumption.hpp>

VAO::VAO()
{
    glCreateVertexArrays(1, &ID);
    ASSUME(glGetError() == GL_NO_ERROR);
    ASSUME(ID != 0);
}

VAO::~VAO()
{
    deleteArray();
}

void VAO::bind() const
{
    ASSUME(ID != 0);
    glBindVertexArray(ID);
    ASSUME(glGetError() == GL_NO_ERROR);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
    ASSUME(glGetError() == GL_NO_ERROR);
}

void VAO::deleteArray()
{
    if (ID != 0)
    {
        glDeleteVertexArrays(1, &ID);
        ASSUME(glGetError() == GL_NO_ERROR);
        ID = 0;
    }
}

void VAO::linkVBO(GLuint vbo_id, unsigned int layout_loc, GLint element_size)
{
    ASSUME(ID != 0);
    glVertexArrayVertexBuffer(ID, layout_loc, vbo_id, 0, element_size * sizeof(float));
    ASSUME(glGetError() == GL_NO_ERROR);
    glEnableVertexArrayAttrib(ID, layout_loc); 
    ASSUME(glGetError() == GL_NO_ERROR);
    glVertexArrayAttribFormat(ID, layout_loc, element_size, GL_FLOAT, GL_FALSE, 0);
    ASSUME(glGetError() == GL_NO_ERROR);
    glVertexArrayAttribBinding(ID, layout_loc, layout_loc);
    ASSUME(glGetError() == GL_NO_ERROR);
}

void VAO::bindVertices(std::vector<float> const &vertices)
{
    _VBO_vertex = std::make_unique<VBO>();
    _VBO_vertex->sendData(vertices);
    linkVBO(_VBO_vertex->ID, 0, 3);
}

void VAO::bindNormals(std::vector<float> const &normals)
{
    _VBO_normal = std::make_unique<VBO>();
    _VBO_normal->sendData(normals);
    linkVBO(_VBO_normal->ID, 1, 3);
}

void VAO::bindIndices(std::vector<unsigned int> const &indices)
{
    _EBO = std::make_unique<EBO>();
    _EBO->sendData(indices);
    glVertexArrayElementBuffer(ID, _EBO->ID);
}

void VAO::bindTextureCoordinates(std::vector<float> const &texture_coordinates)
{
    _VBO_tex_coord = std::make_unique<VBO>();
    _VBO_tex_coord->sendData(texture_coordinates);
    linkVBO(_VBO_tex_coord->ID, 2, 2);
}

void VAO::bindBuffers(std::vector<float> const &vertices, 
                      std::vector<float> const &normals,
                      std::vector<unsigned int> const &indices,
                      std::vector<float> const &texture_coordinates)
{    
    bindVertices(vertices);
    if (!normals.empty())
        bindNormals(normals);
    if (!indices.empty())
        bindIndices(indices);
    if (!texture_coordinates.empty())
        bindTextureCoordinates(texture_coordinates);

    vertices_size = vertices.size();
    normals_size = normals.size();
    indices_size = indices.size();
    texture_coordinates_size = texture_coordinates.size();
}
