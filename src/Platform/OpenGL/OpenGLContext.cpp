// vendor
#define GLFW_INCLUDE_NONE
#include "../../../vendor/GL/include/glew.h"
#include "../../../vendor/GLFW/include/glfw3.h"
// project header
#include "../OpenGL/OpenGLContext.hpp"
// std library
#include <iostream>
#include <string>

void OpenGLContext::Init()
{
    // Make context current
    glfwMakeContextCurrent(m_pWindowHandle);
    // Tells GLFW what version of opengl we are using: 3.3.0 NVIDIA 552.44
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we only want the modern functions via core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize GLEW (or any other OpenGL function loader)
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failure" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW.");
    }
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_pWindowHandle);
}