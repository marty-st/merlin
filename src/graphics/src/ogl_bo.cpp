#include <graphics/ogl_bo.hpp>

OpenGLBufferObject::OpenGLBufferObject()
{
    glCreateBuffers(1, &ID);
    ASSUME(glGetError() == GL_NO_ERROR);
    ASSUME(ID != 0);
}

OpenGLBufferObject::~OpenGLBufferObject()
{
    deleteBuffer();
}

void OpenGLBufferObject::deleteBuffer()
{
    if (ID != 0)
    {
        glDeleteBuffers(1, &ID);
        ASSUME(glGetError() == GL_NO_ERROR);
        ID = 0;
    }
}
