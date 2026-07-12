#pragma once
#include "RenderBaseInterface.hpp"
#include "RenderDefs.hpp"
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
    };
}