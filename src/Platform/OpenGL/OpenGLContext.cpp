// vendor
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project header
#include "OpenGLContext.hpp"
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
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "GLEW initialization failure" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW.");
    }
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_pWindowHandle);
}