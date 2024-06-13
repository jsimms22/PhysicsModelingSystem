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

constexpr int STRIDE {8};
constexpr int INSTANCE_STRIDE {3};
constexpr int MAX_INSTANCES {20000};
constexpr int VERTEX_LIMIT {2000};

Modelf createModel(Meshf mesh);

void destroyModel(Modelf model);

void processVertex(std::vector<float>& vertex_bin, 
                    std::vector<std::string>& vertexData, 
                    std::array<Vertex3f, VERTEX_LIMIT>& v, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vt, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vn);

void loadObject(std::string filename, std::vector<float>& vertex_bin);

Meshf createMeshFromFile(std::string filename, bool instanced);

Meshf createMeshFromArray(float vertices[], unsigned int indices[]);

void destroyMesh(Meshf mesh);
