#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util.hpp>
#include <stdint.h>
#include <string>
namespace glRender
{
    class glEBO final
    {
        public:
        glEBO(GLfloat *f_data, const GLsizeiptr f_size, const GLenum f_usage);
        void Bind();
        void Unbind();
        void Delete();
        ~glEBO() = default;
        private:
        DELETE_COPY_MOVE_OPERATORS(glEBO);
        GLuint m_id{};
    };
}