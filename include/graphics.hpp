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
#include "modelClass.hpp"

std::vector<vertexf> FloorVertex(size_t vertexCount, float length, float width);

std::vector<unsigned int> FloorIndex(size_t vertexCount);

void DrawModelMesh(std::shared_ptr<Model> pModel, bool bInstanced);

// void drawInstanced(Mesh& mesh, unsigned int shaderID, 
//                    unsigned int mode, int num, float scale);