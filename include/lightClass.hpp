#pragma once
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "fwd_math.hpp"
#include "types.hpp"
#include "modelClass.hpp"

template <typename UNIT>
class Light : public Model<UNIT>
{
public:
    vec4f color;

    Light(Mesh<UNIT> _m, vec3<UNIT> _pos, vec3<UNIT> _rot, 
             vec4<UNIT> _color, UNIT _s, unsigned int _rendMethod)
        : Model<UNIT>{_m, _pos, _rot, _s, _rendMethod}
    { this->color = _color; }

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
// Type aliases
using Lightf = Light<float>;
using Lightd = Light<double>;