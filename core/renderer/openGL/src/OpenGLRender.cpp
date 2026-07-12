
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
    // Simple shaders for drawing a colored triangle.
    // In a real application, you would load these from files.
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    static utl::AutoRegister<render::RenderInf, OpenGlRender, render::RenderConfig> reg_bus("OpenGL");

    OpenGlRender::OpenGlRender(const render::RenderConfig &f_config)
    : window(nullptr), m_shaderProgram(0), m_VAO(0), m_VBO(0)
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

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // --- Shader Compilation ---
        // Vertex Shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // (Error checking for shader compilation would go here)

        // Fragment Shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // (Error checking for shader compilation would go here)

        // Link shaders into a shader program
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);
        // (Error checking for shader linking would go here)

        // Delete the individual shaders as they're now linked into the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // --- Vertex Data and Buffers ---
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.5f,  0.5f, 0.0f,  // top

            0.5f, 0.5f, 0.0f, // left
             -0.5f, 0.5f, 0.0f, // right
             -0.5f,  -0.5f, 0.0f  // top
        };

        // 1. Generate and bind a Vertex Array Object (VAO)
        // A VAO stores all the state needed to supply vertex data
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // 2. Generate a Vertex Buffer Object (VBO), bind it, and copy vertex data to it
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 3. Set the vertex attribute pointers
        // This tells OpenGL how to interpret the vertex data in the VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // 4. Unbind the VBO and VAO. It's good practice to unbind to avoid accidental modification.
        // The VAO still remembers the VBO and the attribute pointers.
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        LOG_INFO("OpenGLRender created with width: %d, height: %d", f_config.m_width, f_config.m_height);
    }

    OpenGlRender::~OpenGlRender()
    {
        // Clean up GPU resources
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteProgram(m_shaderProgram);

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
        glClearColor(0.2f, 0.3f,
                     0.3f, 1.0f);

        while (!glfwWindowShouldClose(window))
        {
            // Input
            glfwPollEvents(); 

            // Rendering
            glClear(GL_COLOR_BUFFER_BIT); 
            glUseProgram(m_shaderProgram);
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Swap buffers
            glfwSwapBuffers(window);
        }

        return render::RenderErr::NO_ERR;
    }

}