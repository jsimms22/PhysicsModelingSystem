#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <filesystem>
// project headers
#include "meshClass.hpp"
#include "fwd_math.hpp"
#include "utility.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

namespace fs = std::filesystem;

template <typename UNIT>
class Model
{
public:
    Mesh mesh;
    vec3<UNIT> position;
    vec3<UNIT> rotation;
    UNIT scale;
    unsigned int renderMethod;

    Model(Mesh _m, vec3<UNIT> _pos, vec3<UNIT> _rot, UNIT _s, unsigned int _rendMethod)
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

template <typename UNIT>
class Light : public Model<UNIT>
{
public:
    vec4f color;

    Light(Mesh _m, vec3<UNIT> _pos, vec3<UNIT> _rot, 
             vec4<UNIT> _color, UNIT _s, unsigned int _rendMethod)
        : Model<UNIT>{_m, _pos, _rot, _s, _rendMethod}
    { this->color = _color; }

    void setPos(const vec3f _pos) { this->position = _pos; }
    void setColor(const vec4f _color) { this->color = _color; }
    void setScale(const float _s) { this->scale = _s; }

    void input(GLFWwindow* window) 
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            this->position.data[2] -= 1.0;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            this->position.data[2] += 1.0;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            this->position.data[0] -= 1.0;
        } 
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            this->position.data[0] += 1.0;
        } 
    }
};
// Type aliases
using Lightf = Light<float>;
using Lightd = Light<double>;
