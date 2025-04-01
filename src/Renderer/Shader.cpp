// project headers
#include "../Renderer/Shader.hpp"
#include <cerrno>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
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

void Shader::SetInteger(const std::string& uniformName, const int32_t& value)
{
    Bind();
    glUniform1i(GetUniformLocation(uniformName), value);
    Unbind();
}

void Shader::SetUnsigned(const std::string& uniformName, const uint32_t& value)
{
    Bind();
    glUniform1ui(GetUniformLocation(uniformName), value);
    Unbind();
}

void Shader::SetFloat(const std::string& uniformName, const float& value)
{
    Bind();
    glUniform1f(GetUniformLocation(uniformName), value);
    Unbind();
}

void Shader::SetUniform2fv(const std::string& uniformName, const vec2f& values)
{
    Bind();
    glUniform2fv(GetUniformLocation(uniformName), 1, values.data);
    Unbind();
}

void Shader::SetUniform3fv(const std::string& uniformName, const vec3f& values)
{
    Bind();
    glUniform3fv(GetUniformLocation(uniformName), 1, values.data);
    Unbind();
}

void Shader::SetUniform4fv(const std::string& uniformName, const vec4f& values)
{
    Bind();
    glUniform4fv(GetUniformLocation(uniformName), 1, values.data);
    Unbind();
}

void Shader::SetUniform3fm(const std::string& uniformName, const mat3x3f& values, bool transpose /* = false */)
{
    Bind();
    glUniformMatrix3fv(GetUniformLocation(uniformName), 1, transpose, values.data->data);
    Unbind();
}

void Shader::SetUniform4fm(const std::string& uniformName, const mat4x4f& values, bool transpose /* = false */)
{
    Bind();
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, transpose, values.data->data);
    Unbind();
}

uint32_t Shader::GetUniformLocation(const std::string& uniformName) 
{
    std::unordered_map<std::string, int32_t>::const_iterator itr = m_uniformLocationCache.find(uniformName);

    int32_t location = -1;

    if (itr == m_uniformLocationCache.end()) {
        location = glGetUniformLocation(m_ID, uniformName.c_str());
        m_uniformLocationCache.insert_or_assign(uniformName,location);
    } else {
        location = itr->second;
    }

#ifdef DEBUG
    // If no id or return is -1
    if (location == -1) {
        // Do not throw, might be useful to continue, but inform caller
        std::cout << "Warning: uniform '" << uniformName << "' does not exist." << std::endl;
    }
#endif 

    return location; 
}

std::string Shader::ReadFileContents(const std::string& filename)
{
#ifdef DEBUG
    std::cout << "Compiling: " << filename << std::endl;
#endif
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

uint32_t Shader::CompileShader(uint32_t type, const std::string& fileText)
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
        return 0;
    }

    return id;
}