#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../Scene/modelClass.hpp"
// std library
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cmath>

class IModel;

std::vector<vertexf> FloorVertex(unsigned int vertexCount, float length, float width);

std::vector<unsigned int> FloorIndex(unsigned int vertexCount);

void DrawModelMesh(std::shared_ptr<IModel> pModel, bool bInstanced);

// void DrawInstancedMesh(std::shared_ptr<IModel> pModel);