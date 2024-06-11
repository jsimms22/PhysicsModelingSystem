#pragma once

// std library
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <memory>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

namespace fs = std::filesystem;

std::string readFileContents(std::string filename);

unsigned int createShader(std::string vertexFile, std::string fragmentFile);

void detachShader();

void destroyShader(unsigned int shaderID);