// project headers
#include <stdexcept>
#include "../include/hardware_input.hpp"

bool GLFWContext::Initialize()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "GLFW init failure" << std::endl;
        return m_bInitialized;
    }

    // Tells GLFW what version of opengl we are using: 3.3.0 NVIDIA 552.44
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we only want the modern functions via core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_bInitialized = true;
    return m_bInitialized;
}

Window::Window(const std::unique_ptr<GLFWContext>& context, int width, int height, const char* title) 
{
    if (!context->Initialize()) {
        throw std::runtime_error("Failed to initialize GLFW context.");
    }

    // Create window
    m_pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_pWindow) {
        std::cout << "Window creation failure" << std::endl;
        throw std::runtime_error("Failed to create GLFW window.");
    }

    // Make context current
    glfwMakeContextCurrent(m_pWindow);

    // Initialize GLEW (or any other OpenGL function loader)
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failure" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW.");
    }

    // OpenGL settings
    glViewport(0, 0, width, height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3.0f);
    // Vsync
    glfwSwapInterval(1);
}

Window::~Window() { if (m_pWindow) { glfwDestroyWindow(m_pWindow); } }

void Window::SwapBuffers() { glfwSwapBuffers(m_pWindow); }

void Window::PollEvents() { glfwPollEvents(); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_pWindow); }

void Window::ProcessInput()
{
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) { 
        glfwSetWindowShouldClose(m_pWindow, true);
    }
}