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

class Model
{
public:
    Mesh mesh;
    vec3f position;
    vec3f rotation;
    float scale;
    unsigned int renderMethod;

    Model(Mesh _m, vec3f _pos, vec3f _rot, float _s, unsigned int _rendMethod)
        : mesh{_m}, position{_pos}, rotation{_rot}, scale{_s}, renderMethod{_rendMethod} { }
    
    void destroyMesh();
     ~Model() { destroyMesh(); }
};

class Light : public Model
{
public:
    vec4f color;

    Light(Mesh _m, vec3f _pos, vec3f _rot, vec4f _color, float _s, unsigned int _rendMethod)
        : Model{_m, _pos, _rot, _s, _rendMethod} { this->color = _color; }

    void setPos(const vec3f _pos) { this->position = _pos; }
    void setColor(const vec4f _color) { this->color = _color; }
    void setScale(const float _s) { this->scale = _s; }
    void input(GLFWwindow* window);

    void updateUniform(unsigned int shaderID, std::string uniform);
};
