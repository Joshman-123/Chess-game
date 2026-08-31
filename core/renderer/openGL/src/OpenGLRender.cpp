
#include "AutoRegister.hpp"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.hpp"
#include <iostream>
#include <vector>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OpenGLRender.hpp"
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

namespace glRender
{
    static const std::filesystem::path kProjectRoot = std::filesystem::path(__FILE__)
        .parent_path()
        .parent_path()
        .parent_path()
        .parent_path()
        .parent_path();

    static const std::string kVertexShaderPath = (kProjectRoot / "core" / "renderer" / "openGL" / "src" / "Shaders" / "VertexShader.txt").lexically_normal().string();
    static const std::string kFragmentShaderPath = (kProjectRoot / "core" / "renderer" / "openGL" / "src" / "Shaders" / "FragmentShader.txt").lexically_normal().string();
    static const std::string kTexturePath = (kProjectRoot / "ChessPictures" / "black" / "Bishop.png").lexically_normal().string();

    static utl::AutoRegister<render::RenderInf, OpenGlRender, render::RenderConfig> s_glHook("OpenGL");

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

        m_shader = std::make_unique<glRender::Shader>(kVertexShaderPath.c_str(), kFragmentShaderPath.c_str());

        std::vector<float> vertices{};

        const uint8_t floatsPerVertex = 6; // 3 for position, 3 for color
        const int squaresPerRow = 8;
        generateGridVerticesAndIndices(vertices, this->indices, squaresPerRow, floatsPerVertex);

        m_vao = std::make_unique<glRender::glVAO>();
        m_vao->Bind();

        // 2. Generate a Vertex Buffer Object (VBO), bind it, and copy vertex data to it
        m_vbo = std::make_unique<glRender::glVBO>(vertices.data(), vertices.size() * sizeof(float), GL_STATIC_DRAW);

        // Generate and bind the Element Buffer Object (EBO)
        m_ebo = std::make_unique<glRender::glEBO>(indices.data(), indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

        // 3. Set the vertex attribute pointers while the VAO is still bound.
        // This tells OpenGL how to interpret the vertex data in the VBO.
        // Position attribute
        m_vao->LinkVBO(*m_vbo, 0, floatsPerVertex * sizeof(float), (void*)0);
        // Color attribute
        m_vao->LinkVBO(*m_vbo, 1, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));

        m_ebo->Bind();
        m_vao->Unbind();

        LOG_INFO("OpenGLRender created with width: %d, height: %d", f_config.m_width, f_config.m_height);
    }

    void OpenGlRender::generateGridVerticesAndIndices(std::vector<float> &vertices, std::vector<unsigned int> &indices, int squaresPerRow, int floatsPerVertex)
    {
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
        const int numSquares = squaresPerRow * squaresPerRow;
        const int verticesPerSquare = 4;
        const int totalVertices = numSquares * verticesPerSquare;
        const int totalFloats = totalVertices * floatsPerVertex;

        vertices.resize(totalFloats);
        indices.resize(numSquares * 6);

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
                    r = 0.20f; g = 0.30f; b = 0.15f;
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
    }

    OpenGlRender::~OpenGlRender()
    {
        // Clean up GPU resources
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        m_shader->Deactivate(); // Deactivate the shader program

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
        int width,height, nrChannels;
        unsigned char *data = stbi_load(kTexturePath.c_str(), &width, &height, &nrChannels, 0);

        GLuint texture{};
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    
        while (!glfwWindowShouldClose(window))
        {
            // Input
            glfwPollEvents(); 

            // Rendering
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->Activate();

            m_vao->Bind();

            m_ebo->Bind();

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

            // Swap buffers
            glfwSwapBuffers(window);
        }

        return render::RenderErr::NO_ERR;
    }

}