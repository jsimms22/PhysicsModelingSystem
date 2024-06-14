#pragma once

// std library
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <memory>
#include <cerrno>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

namespace fs = std::filesystem;

std::string readFileContents(fs::path filename);

unsigned int compileShader(unsigned int type, const std::string& fileText);

class Shader
{
public:
    unsigned int ID;
    Shader(fs::path vertexFile, fs::path fragmentFile);

    void attach() { glUseProgram(this->ID); }
    void detach() { glUseProgram(0); }
    void destroy() { glDeleteProgram(this->ID); }
};