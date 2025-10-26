// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project headers
#include "WindowsWindow.hpp"

#include "../../Events/WindowEvents.hpp"
#include "../../Events/KeyEvents.hpp"
#include "../../Events/MouseEvents.hpp"

#include "../../Renderer/GraphicsContext.hpp"
// std library
#include <iostream>
#include <string>

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

#ifdef DEBUG
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif //DEBUG

    // Create window
    m_pWindow = glfwCreateWindow(static_cast<int>(m_data.width), static_cast<int>(m_data.height), m_data.title.c_str(), nullptr, nullptr);
    if (!m_pWindow) { std::cerr << "WindowsWindow creation failure" << std::endl; }

    m_upContext = GraphicsContext::Create(m_pWindow);
    m_upContext->Init();

    // Set our data struct as the pointer format
    glfwSetWindowUserPointer(m_pWindow,&m_data);

    glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, const int width, const int height) -> void
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowResizeEvent event{static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)};
            data.width = static_cast<std::uint32_t>(width);
            data.height = static_cast<std::uint32_t>(height);
            data.EventCallback(event);
        });
    glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window) -> void
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowCloseEvent event;
            data.EventCallback(event);
        });

    glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) -> void
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

    glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* window, int button, int action, int /*mods*/) -> void
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

void WindowsWindow::UpdateWindowTitle(double dt, std::size_t numActive)
{
    std::string title = "FPS: " + std::to_string(static_cast<int>((1.0/dt)-4.0)) + " | Balls: " + std::to_string(numActive);
    glfwSetWindowTitle(m_pWindow, title.c_str());
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    m_upContext->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    m_data.vsync = enabled;
}