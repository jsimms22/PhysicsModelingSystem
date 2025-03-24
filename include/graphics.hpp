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
#include "fwd_math.hpp"
#include "meshClass.hpp"

std::vector<vertexf> floorVertex(size_t vertexCount, float length, float width);

std::vector<unsigned int> floorIndex(size_t vertexCount);

void drawMesh(std::shared_ptr<Mesh> mesh, Shader& shader, unsigned int mode, 
              vec3f& position, vec3f& rotation, float scale);

// void drawInstanced(Mesh& mesh, unsigned int shaderID, 
//                    unsigned int mode, int num, float scale);