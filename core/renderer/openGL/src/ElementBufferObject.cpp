
#include <ElementBufferObject.hpp>
namespace glRender
{
    glEBO::glEBO(GLfloat *f_data, const GLsizeiptr f_size, const GLenum f_usage)
    {
        // 2. Generate a Vertex Buffer Object (VBO), bind it, and copy vertex data to it
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, f_size, f_data, f_usage);
    }
    void glEBO::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
    void glEBO::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    void glEBO::Delete()
    {
        glDeleteBuffers(1, &m_id);
    }

}