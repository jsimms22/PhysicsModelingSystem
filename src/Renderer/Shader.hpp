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

uint32_t CompileShader(uint32_t type, const std::string& fileText);

class Shader
{
public:
    // Constructors
    Shader(fs::path vertexFile, fs::path fragmentFile);
    // Destructors
    ~Shader() { Destroy(); }

    void Attach() { glUseProgram(m_ID); }
    void Detach() { glUseProgram(0); }

    void Destroy() { glDeleteProgram(m_ID); }

    void AddUniformTypeName(const std::string& name) {}

    uint32_t GetID() const { return m_ID; }

private:
    uint32_t m_ID;
};