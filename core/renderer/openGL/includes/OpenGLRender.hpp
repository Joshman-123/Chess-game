#pragma once
#include "RenderBaseInterface.hpp"
#include "RenderDefs.hpp"
#include <Shader.hpp>
#include <VertexBufferObject.hpp>
#include <VertexArrayObject.hpp>
#include <ElementBufferObject.hpp>
#include <Util.hpp>
namespace glRender
{
    class OpenGlRender final : public render::RenderInf
    {
        public:
        OpenGlRender(const render::RenderConfig &f_config);
        virtual ~OpenGlRender();
        virtual render::RenderErr execute() override;
        private:
        DELETE_COPY_MOVE_OPERATORS(OpenGlRender);
        GLFWwindow *window;
        unsigned int m_shaderProgram;
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_EBO;
        std::vector<unsigned int> indices{};
        std::unique_ptr<glRender::Shader> m_shader = nullptr;
        std::unique_ptr<glRender::glVAO> m_vao = nullptr;
        std::unique_ptr<glRender::glVBO> m_vbo = nullptr;
        std::unique_ptr<glRender::glEBO> m_ebo = nullptr;
    };
}