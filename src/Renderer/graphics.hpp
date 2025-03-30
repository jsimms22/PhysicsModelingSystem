#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../Scene/Model.hpp"
// std library
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cmath>

class IModel;

std::vector<vertexf> FloorVertex(uint32_t vertexCount, float length, float width);

std::vector<uint32_t> FloorIndex(uint32_t vertexCount);

void DrawModelMesh(std::shared_ptr<IModel> pModel);

// void DrawInstancedMesh(std::shared_ptr<IModel> pModel);