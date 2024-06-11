// project headers
#include "../include/shaders.hpp"

std::string readFileContents(std::string filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int createShader(std::string vertexFile, std::string fragmentFile)
{
    GLint success = 0;
    GLint logSize = 0;

    // Create a shader object and compile it during runtime
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource = readFileContents(vertexFile);
    // std::cout << "vertexShaderSource output: " + vertexShaderSource << std::endl;
    const char* vertex_charstr = vertexShaderSource.c_str();
    // std::cout << "vertex_charstr output: " << vertex_charstr << std::endl;
    glShaderSource(vertexShader, 1, &vertex_charstr, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* infoLog;
        glGetShaderInfoLog(vertexShader, logSize, &logSize, infoLog);
        glDeleteShader(vertexShader);
        if (infoLog != NULL) { printf("Vertex Shader: %s\n", infoLog); }
    }

    // Perform the same steps for the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource = readFileContents(fragmentFile);
    // std::cout << "fragmentShaderSource output: " + fragmentShaderSource << std::endl;
    const char* fragment_charstr = fragmentShaderSource.c_str();
    // std::cout << "fragment_charstr output: " << fragment_charstr << std::endl;
    glShaderSource(fragmentShader, 1, &fragment_charstr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar* infoLog;
        glGetShaderInfoLog(fragmentShader, logSize, &logSize, infoLog);
        glDeleteShader(fragmentShader);
        if (infoLog != NULL) { printf("Fragment Shader: %s\n", infoLog); }
    }

    // Create a shader program and link the two shader steps together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

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