// vendors
// project headers
#include "../Windows/WindowsWindow.hpp"
#include "../../Events/WindowEvents.hpp"
#include "../../Events/KeyEvents.hpp"
#include "../../Events/MouseEvents.hpp"
// std library
#include <string>
#include <iostream>
#include <stdexcept>

static void GLFWErrorCallback(int error, const char* desc)
{
    throw std::runtime_error("GLFW Error Code(" + std::to_string(error) + "): " + desc);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    m_data.width = props.width;
    m_data.height = props.height;
    m_data.title = props.title;

    // Initialize GLFW (ONLY DO ONCE)
    int success = glfwInit();
    if (!success) { std::cerr << "GLFW init failure" << std::endl; }
    glfwSetErrorCallback(GLFWErrorCallback);

#ifdef debug
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    // Create window
    m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    if (!m_pWindow) { std::cerr << "WindowsWindow creation failure" << std::endl; }
    
    m_upContext = GraphicsContext::Create(m_pWindow);
    m_upContext->Init();

    // Set our data struct as the pointer format
    glfwSetWindowUserPointer(m_pWindow,&m_data);

    glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, int width, int height) -> void 
        { 
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent event(width, height);
            data.width = static_cast<uint32_t>(width);
            data.height = static_cast<uint32_t>(height);
            data.EventCallback(event);
        });
    glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window) -> void 
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowCloseEvent event;
            data.EventCallback(event);
        });

    glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void 
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleaseEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressEvent event(key, 1); // need to properly extract the repeat count at some point
                    data.EventCallback(event);
                    break;
                }
            }
        });
    
    glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* window, int button, int action, int mods) -> void
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MousePressEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleaseEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(m_pWindow, [](GLFWwindow* window, double offsetX, double offsetY) -> void
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            MouseScrollEvent event(static_cast<float>(offsetX),static_cast<float>(offsetY));
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* window, double posX, double posY) -> void
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            MouseMoveEvent event(static_cast<float>(posX),static_cast<float>(posY));
            data.EventCallback(event);
        });

    
    SetVSync(true);
}

WindowsWindow::~WindowsWindow() { if (m_pWindow) { glfwDestroyWindow(m_pWindow); } }

void WindowsWindow::UpdateWindowTitle(double dt, int numActive)
{
    std::string title = "FPS: " + std::to_string(static_cast<int>((1.0/dt)-4.0)) + " | Balls: " + std::to_string(numActive);
    glfwSetWindowTitle(m_pWindow, title.c_str());
}