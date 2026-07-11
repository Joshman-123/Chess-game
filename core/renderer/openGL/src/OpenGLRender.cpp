
#include "AutoRegister.hpp"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include "OpenGLRender.hpp"
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

namespace glRender
{
    static utl::AutoRegister<render::RenderInf, OpenGlRender, render::RenderConfig> reg_bus("OpenGL");

    OpenGlRender::OpenGlRender(const render::RenderConfig &f_config)
    {
        if (!glfwInit())
        {
            LOG_INFO("Failed to initialize GLFW\n");
            return;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(f_config.m_width,f_config.m_height, f_config.m_windowName.c_str(), NULL, NULL);

        if (window == NULL)
        {
            LOG_ERROR("Failed to open GLFW window\n");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_ERROR("Failed to initialize GLAD\n");
            return;
        }

        glViewport(0, 0, 800, 600);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        LOG_INFO("OpenGLRender created with width: %d, height: %d", f_config.m_width, f_config.m_height);
    }

    OpenGlRender::~OpenGlRender()
    {
        glfwTerminate();
        if(window != nullptr)
        {
            glfwDestroyWindow(window);
        }

        LOG_INFO("OpenGLRender destroyed");
    }

    render::RenderErr OpenGlRender::execute()
    {
        LOG_INFO("Calling OpenGLRender::execute");
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
        }

        return render::RenderErr::NO_ERR;
    }

}