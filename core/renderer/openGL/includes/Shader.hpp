#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Util.hpp>
#include <stdint.h>
#include <string>
namespace glRender
{

    class Shader final
    {
        public:
        Shader(const char *f_vertexShaderSource, const char *f_fragmentShaderSource);
        void Activate();
        void Deactivate();
        ~Shader() = default;
        private:
        std::string get_file_contents(const char *filename);
        DELETE_COPY_MOVE_OPERATORS(Shader);
        GLuint m_shaderProgram{};

    };
}