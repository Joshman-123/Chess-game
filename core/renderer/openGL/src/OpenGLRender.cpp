
#include "AutoRegister.hpp"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include <iostream>
#include <vector>
#include "OpenGLRender.hpp"
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

namespace glRender
{
    // Simple shaders for drawing a colored triangle.
    // In a real application, you would load these from files.
    const char *vertexShaderSource = R"glsl(#version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        out vec3 ourColor;
        void main()
        {
           gl_Position = vec4(aPos, 1.0);
           ourColor = aColor;
        }
    )glsl";
    const char *fragmentShaderSource = R"glsl(#version 330 core
        out vec4 FragColor;
        in vec3 ourColor;
        void main()
        {
           FragColor = vec4(ourColor, 1.0f);
        }
    )glsl";

    static utl::AutoRegister<render::RenderInf, OpenGlRender, render::RenderConfig> reg_bus("OpenGL");

    OpenGlRender::OpenGlRender(const render::RenderConfig &f_config)
    : window(nullptr), m_shaderProgram(0), m_VAO(0), m_VBO(0), m_EBO(0)
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
        // Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
        }

        // Fragment Shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // (Error checking for shader compilation would go here)
        // Check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
        }

        // Link shaders into a shader program
        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);
        glLinkProgram(m_shaderProgram);
        // (Error checking for shader linking would go here)
        // Check for linking errors
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
        }

        // Delete the individual shaders as they're now linked into the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


    

    /*          Default Grid Dimension of Open GL 
      (-1,1)-----------------(0,1)-----------------(1,1)
        |                      |                     |
        |                      |                     |
        |                      |                     |
        |                      |                     |
        |                      |                     |
      (-1,0)_________________(0,0)_________________(1,0)
        |                      |                     |
        |                      |                     |
        |                      |                     |
        |                      |                     |
        |                      |                     |
      (-1,-1)----------------(0,-1)----------------(1,-1)

        */
        // --- Vertex Data and Buffers ---
        const int squaresPerRow = 8;
        const int numSquares = squaresPerRow * squaresPerRow;
        const int verticesPerSquare = 4;
        const int floatsPerVertex = 6; // 3 for position (XYZ), 3 for color (RGB)
        const int totalVertices = numSquares * verticesPerSquare;
        const int totalFloats = totalVertices * floatsPerVertex;

        std::vector<float> vertices(totalFloats);
        
        const float squareSize = 2.0f / squaresPerRow; // Size of each square in clip space (-1.0 to 1.0)
        const float startX = -1.0f;
        const float startY = 1.0f;

        int vertexIndex = 0;
        for (int row = 0; row < squaresPerRow; ++row)
        {
            for (int col = 0; col < squaresPerRow; ++col)
            {
                float x = startX + col * squareSize;
                float y = startY - row * squareSize;

                // Determine the color of the square
                float r, g, b;
                if ((row + col) % 2 == 0)
                {
                    // White square (a slightly off-white looks better)
                    r = 0.9f; g = 0.9f; b = 0.9f;
                }
                else
                {
                    // Black square (a dark gray looks better)
                    r = 0.2f; g = 0.2f; b = 0.2f;
                }

                // Top-left
                vertices[vertexIndex++] = x;
                vertices[vertexIndex++] = y;
                vertices[vertexIndex++] = 0.0f;
                vertices[vertexIndex++] = r;
                vertices[vertexIndex++] = g;
                vertices[vertexIndex++] = b;

                // Top-right
                vertices[vertexIndex++] = x + squareSize;
                vertices[vertexIndex++] = y;
                vertices[vertexIndex++] = 0.0f;
                vertices[vertexIndex++] = r;
                vertices[vertexIndex++] = g;
                vertices[vertexIndex++] = b;

                // Bottom-right
                vertices[vertexIndex++] = x + squareSize;
                vertices[vertexIndex++] = y - squareSize;
                vertices[vertexIndex++] = 0.0f;
                vertices[vertexIndex++] = r;
                vertices[vertexIndex++] = g;
                vertices[vertexIndex++] = b;

                // Bottom-left
                vertices[vertexIndex++] = x;
                vertices[vertexIndex++] = y - squareSize;
                vertices[vertexIndex++] = 0.0f;
                vertices[vertexIndex++] = r;
                vertices[vertexIndex++] = g;
                vertices[vertexIndex++] = b;
            }
        }

        const int indicesPerSquare = 6; // 2 triangles per square
        const int totalIndices = numSquares * indicesPerSquare;
        indices.resize(totalIndices);

        int index = 0;
        for (int i = 0; i < numSquares; ++i)
        {
            unsigned int baseVertex = i * verticesPerSquare;
            indices[index++] = baseVertex + 0; // Top-left
            indices[index++] = baseVertex + 1; // Top-right
            indices[index++] = baseVertex + 3; // Bottom-left

            indices[index++] = baseVertex + 1; // Top-right
            indices[index++] = baseVertex + 2; // Bottom-right
            indices[index++] = baseVertex + 3; // Bottom-left
        }
        
        // 1. Generate and bind a Vertex Array Object (VAO)
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO); // Bind the VAO *before* configuring buffers and attributes

        // 2. Generate a Vertex Buffer Object (VBO), bind it, and copy vertex data to it
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Generate and bind the Element Buffer Object (EBO)
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // 3. Set the vertex attribute pointers
        // This tells OpenGL how to interpret the vertex data in the VBO
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


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
        glDeleteBuffers(1, &m_EBO);
        glDeleteProgram(m_shaderProgram);

        if(window != nullptr)
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();

        LOG_INFO("OpenGLRender destroyed");
    }

    render::RenderErr OpenGlRender::execute()
    {
        LOG_INFO("Calling OpenGLRender::execute");
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        while (!glfwWindowShouldClose(window))
        {
            // Input
            glfwPollEvents(); 

            // Rendering
            glClear(GL_COLOR_BUFFER_BIT); 
            glUseProgram(m_shaderProgram);
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

            // Swap buffers
            glfwSwapBuffers(window);
        }

        return render::RenderErr::NO_ERR;
    }

}