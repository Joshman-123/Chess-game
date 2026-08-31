
#include <Logger.hpp>
#include <Shader.hpp>
#include <fstream>
#include <sstream>
namespace glRender
{
    Shader::Shader(const char *f_vertexShaderSource, const char *f_fragmentShaderSource)
    {
        std::string vertexShaderSourceStr = get_file_contents(f_vertexShaderSource);
        std::string fragmentShaderSourceStr = get_file_contents(f_fragmentShaderSource);

        if (vertexShaderSourceStr.empty() || fragmentShaderSourceStr.empty())
        {
            LOG_ERROR("ERROR::SHADER::FILE_NOT_FOUND::FALLBACK_USED");
            // Fallback shader sources
        }

        const char *vertexShaderSource = vertexShaderSourceStr.c_str();
        const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

        // --- Shader Compilation ---
        // Vertex Shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // (Error checking for shader compilation would go here)
        // Check for shader compile errors
        int success{};
        char infoLog[512]{};
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
    }

    void Shader::Activate()
    {
        glUseProgram(m_shaderProgram);

    }

    void Shader::Deactivate()
    {
        glDeleteProgram(m_shaderProgram);
    }

    std::string Shader::get_file_contents(const char *filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            LOG_ERROR("ERROR::SHADER::FILE_NOT_FOUND: %s", filename);
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }

}