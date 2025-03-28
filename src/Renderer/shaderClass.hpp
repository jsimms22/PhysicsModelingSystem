#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// std library
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string ReadFileContents(fs::path filename);

unsigned int CompileShader(unsigned int type, const std::string& fileText);

class Shader
{
public:
    Shader(fs::path vertexFile, fs::path fragmentFile);
    ~Shader() { Destroy(); }

    void Attach() { glUseProgram(m_ID); }
    void Detach() { glUseProgram(0); }
    void Destroy() { glDeleteProgram(m_ID); }
    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID;
};