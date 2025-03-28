#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
// std library
#include <iostream>

class Mouse
{
public:
    Mouse() : m_xpos{0.0}, m_ypos{0.0}, m_pxpos{0.0}, m_pypos{0.0} { }
    // update mouse position
    void UpdateMouse(GLFWwindow* _window, double xx, double yy)
    {
        m_pxpos = xx;
        m_pypos = yy;
        glfwGetCursorPos(_window, &xx, &yy);
    }
    double GetX() const { return m_xpos; }
    double GetY() const { return m_ypos; }
    double GetDX() const { return m_xpos - m_pxpos; }
    double GetDY() const { return m_ypos - m_pypos; }
    
private:
    double m_xpos;
    double m_ypos;
    double m_pxpos;
    double m_pypos;
};