// project headers
#include "../include/shaders.hpp"

std::string readFileContents(std::string filename)
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

unsigned int createShader(std::string vertexFile, std::string fragmentFile)
{
    // Create a shader object and compile it during runtime
    std::string vertexShaderSource = readFileContents(vertexFile);
    auto vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    if (vertexShader == 0) {
        std::cout << "shader compilation failure" << std::endl;
        return 0;
    } 

    // Perform the same steps for the fragment shader
    std::string fragmentShaderSource = readFileContents(fragmentFile);
    auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (fragmentShader == 0) {
        std::cout << "shader compilation failure" << std::endl;
        return 0;
    }

    // Create a shader program and link the two shader steps together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    // Make sure to cleanup the individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Return the program
    return shaderProgram;
}

void detachShader()
{
    glUseProgram(0);
}

void destroyShader(unsigned int shaderID)
{
    glDeleteProgram(shaderID);
}