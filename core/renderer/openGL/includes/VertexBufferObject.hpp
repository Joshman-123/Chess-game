#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util.hpp>
#include <stdint.h>
#include <string>
namespace glRender
{
    class glVBO final
    {
        public:
        glVBO(GLfloat *f_data, const GLsizeiptr f_size, const GLenum f_usage);
        void Bind();
        void Unbind();
        void Delete();
        ~glVBO() = default;
        private:
        DELETE_COPY_MOVE_OPERATORS(glVBO);
        GLuint m_id{};

    };
}