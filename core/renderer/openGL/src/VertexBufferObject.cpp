
#include <VertexBufferObject.hpp>
namespace glRender
{
    glVBO::glVBO(GLfloat *f_data, const GLsizeiptr f_size, const GLenum f_usage)
    {
        // 2. Generate a Vertex Buffer Object (VBO), bind it, and copy vertex data to it
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, f_size, f_data, f_usage);
    }

    void glVBO::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }
    void glVBO::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void glVBO::Delete()
    {
        glDeleteBuffers(1, &m_id);
    }

}