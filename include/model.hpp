#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <filesystem>
// project headers
#include "types.hpp"
#include "math.hpp"
#include "utility.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

namespace fs = std::filesystem;

constexpr size_t STRIDE {8};
constexpr size_t INSTANCE_STRIDE {3};
constexpr size_t MAX_INSTANCES {20000};
constexpr size_t VERTEX_LIMIT {2000};

Modelf createModel(Meshf mesh);

void destroyModel(Modelf model);

void processVertex(std::vector<float>& vertex_bin, 
                    std::vector<std::string>& vertexData, 
                    std::array<Vertex3f, VERTEX_LIMIT>& v, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vt, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vn);

void loadObject(std::string filename, std::vector<float>& vertex_bin);

Meshf createMesh(std::string filename, bool instanced);

void destroyMesh(Meshf mesh);
