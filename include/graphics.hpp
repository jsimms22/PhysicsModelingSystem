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

void drawMesh(Meshf& mesh, unsigned int shaderID, GLenum mode, 
              vec3f& position, vec3f& rotation, float scale);

void drawInstanced(Meshf& mesh, unsigned int shaderID, 
                   GLenum mode, int num, float scale);

void drawMeshFromArray(Meshf& mesh, unsigned int shaderID, GLenum mode, int num);