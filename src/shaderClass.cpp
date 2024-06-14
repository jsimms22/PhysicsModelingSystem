// project headers
#include "../include/shaderClass.hpp"

std::string readFileContents(fs::path filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int compileShader(unsigned int type, const std::string& fileText)
{
    // Create a shader object and compile
    unsigned int id = glCreateShader(type);
    // OpenGL requires an lvalue convertable to GLchar**
    const char* src = fileText.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Error Handling
    int result = 0; int length = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msgLog = (char*) alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, msgLog);
        std::cout << "Failed to compile " 
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << " shader." << std::endl;
        glDeleteShader(id);
        //free(msgLog);
        return 0;
    }

    return id;
}

Shader::Shader(fs::path vertexFile, fs::path fragmentFile)
{
    // Create a shader object and compile it during runtime
    std::string vertexSource = readFileContents(vertexFile);
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0) { throw "shader compilation failure"; } 

    // Perform the same steps for the fragment shader
    std::string fragmentSource = readFileContents(fragmentFile);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0) { throw "shader compilation failure"; }

    // Create a shader program and link the two shader steps together
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    glValidateProgram(this->ID);

    // Make sure to cleanup the individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}