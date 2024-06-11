#pragma once

// std library
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cmath>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "../include/math.hpp"

void drawMesh(Meshf mesh, unsigned int shaderID, GLenum mode, 
              vec4f position, vec4f rotation, float scale);

void drawInstanced(Meshf mesh, unsigned int shaderID, 
                   GLenum mode, int num, float scale);