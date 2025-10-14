// vendor
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project header
#include "../OpenGL/OpenGLContext.hpp"
// std library
#include <iostream>
#include <string>

void OpenGLContext::Init()
{
    // Make context current
    glfwMakeContextCurrent(m_pWindowHandle);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize GLEW (or any other OpenGL function loader)
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "GLEW initialization failure" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW.");
    }
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_pWindowHandle);
}