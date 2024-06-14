#pragma once
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "fwd_math.hpp"
#include "types.hpp"

class Lighting
{
public:
    vec3f position{ 0.0, 0.0, 0.0 };
    vec4f color{ 1.0, 1.0, 1.0, 1.0 };
    Meshf mesh;
    float scale = 1.0;

    Lighting(const Meshf _mesh)
        : mesh{_mesh} { }
    
    Lighting(const vec3f _pos, const vec4f _color, Meshf _mesh)
        : position{_pos}, color{_color}, mesh{_mesh} { }

    void setPos(const vec3f _pos) { this->position = _pos; }
    void setColor(const vec4f _color) { this->color = _color; }
    void setScale(const float _s) { this->scale = _s; }

    void input(GLFWwindow* window) 
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            this->position.data[2] -= 0.1;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            this->position.data[2] += 0.1;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            this->position.data[0] -= 0.1;
        } 
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            this->position.data[0] += 0.1;
        } 
    }
};