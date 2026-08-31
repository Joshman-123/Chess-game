
#include <VertexArrayObject.hpp>
namespace glRender
{
    glVAO::glVAO()
    {
        glGenVertexArrays(1, &m_id);
    }

    void glVAO::LinkVBO(glVBO &f_vbo,const GLuint f_layout)
    {
        f_vbo.Bind();
        glVertexAttribPointer(f_layout, 3, GL_FLOAT, GL_FALSE,0 , (void*)0);
        glEnableVertexAttribArray(f_layout);
        f_vbo.Unbind();
        Unbind();
    }
    void glVAO::Bind()
    {
        glBindVertexArray(m_id);
    }
    void glVAO::Unbind()
    {
        glBindVertexArray(0);
    }
    void glVAO::Delete()
    {
        glDeleteVertexArrays(1, &m_id);
    }
}