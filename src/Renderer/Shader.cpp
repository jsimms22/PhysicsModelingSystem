// project headers
#include "../Renderer/Shader.hpp"
#include <cerrno>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

std::string ReadFileContents(fs::path filename)
{
    std::stringstream buffer;
    try 
    {
        std::ifstream file(filename);
        buffer << file.rdbuf();
    } 
    catch (std::ifstream::failure& e)
    {
        std::cout << "Failed to read: " << filename << std::endl;
    }
    return buffer.str();
}

uint32_t CompileShader(uint32_t type, const std::string& fileText)
{
    // Create a shader object and compile
    uint32_t id = glCreateShader(type);

    // OpenGL requires an lvalue convertable to GLchar**
    const char* src = fileText.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Error Handling
    int result = 0; int length = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) 
    {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msgLog = (char*) alloca(static_cast<std::size_t>(length) * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msgLog);

        std::cout << "Failed to compile " 
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << " shader." << std::endl;
        
        std::cout << msgLog << std::endl;

        glDeleteShader(id);
        //free(msgLog);
        return 0;
    }

    return id;
}

Shader::Shader(fs::path vertexFile, fs::path fragmentFile)
{
    // Create a shader object and compile it during runtime
    std::string vertexSource = ReadFileContents(vertexFile);
    uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0) { throw "shader compilation failure"; } 

    // Perform the same steps for the fragment shader
    std::string fragmentSource = ReadFileContents(fragmentFile);
    uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0) { throw "shader compilation failure"; }

    // Create a shader program and link the two shader steps together
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);

    // Make sure to cleanup the individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}