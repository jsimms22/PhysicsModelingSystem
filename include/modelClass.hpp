#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <filesystem>
// project headers
#include "types.hpp"
#include "fwd_math.hpp"
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

void processVertex(std::vector<float>& vertex_bin, 
                    std::vector<std::string>& vertexData, 
                    std::array<Vertex3f, VERTEX_LIMIT>& v, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vt, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vn);

void loadObject(fs::path filename, std::vector<float>& vertex_bin);

Meshf createMesh(fs::path filename, bool instanced);

template <typename UNIT>
class Model
{
public:
    Mesh<UNIT> mesh;
    vec3<UNIT> position;
    vec3<UNIT> rotation;
    UNIT scale;
    unsigned int renderMethod;

    Model(Mesh<UNIT> _m, vec3<UNIT> _pos, vec3<UNIT> _rot, UNIT _s, unsigned int _rendMethod)
        : mesh{_m}, position{_pos}, rotation{_rot}, scale{_s}, renderMethod{_rendMethod} { }
    
    void destroyMesh() {
        glDeleteVertexArrays(1, &(this->mesh.VAO));
        glDeleteBuffers(1, &(this->mesh.VBO));
     }

     ~Model() { destroyMesh(); }
};
// Type aliases
using Modelf = Model<float>;
using Modeld = Model<double>;
