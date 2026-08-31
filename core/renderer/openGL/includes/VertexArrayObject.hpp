#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util.hpp>
#include <stdint.h>
#include <string>
#include <VertexBufferObject.hpp>
namespace glRender
{
    class glVAO final
    {
        public:
        glVAO();
        ~glVAO() = default;
        void LinkVBO(glVBO &f_vbo, const GLuint f_layout, const GLsizei f_stride, const void *f_offset);
        void Bind();
        void Unbind();
        void Delete();
        private:
        DELETE_COPY_MOVE_OPERATORS(glVAO);
        GLuint m_id{};

    };
}