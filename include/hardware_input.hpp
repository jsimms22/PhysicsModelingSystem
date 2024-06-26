#pragma once

// std library
#include <iostream>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

class Mouse
{
private:
    double xpos;
    double ypos;
    double pxpos;
    double pypos;
public:
    Mouse() : xpos{0.0}, ypos{0.0}, pxpos{0.0}, pypos{0.0} { }
    void updateMouse(GLFWwindow* _window, double xx, double yy)
    {
        pxpos = xx;
        pypos = yy;
        glfwGetCursorPos(_window, &xx, &yy);
    }
    double getPosX() const { return xpos; }
    double getPosY() const { return ypos; }
    double getDX() const { return xpos - pxpos; }
    double getDY() const { return ypos - pypos; }
};

void processInput(GLFWwindow* window);