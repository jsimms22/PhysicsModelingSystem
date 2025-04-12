#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../../vendor/GL/include/glew.h"
#include "../../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../../Core/Window.hpp"

#include "../../Renderer/GraphicsContext.hpp"
// std library
#include <iostream>
#include <memory>

class WindowsWindow : public IWindow
{
public:
    WindowsWindow(const WindowProps& props = WindowProps());

    ~WindowsWindow();

    // Update title bar
    void UpdateWindowTitle(double dt, int numActive) override;

    void OnUpdate() override
    {
        glfwPollEvents();
        m_upContext->SwapBuffers();
    }

    std::uint32_t GetWidth() const override { return m_data.width; };
	std::uint32_t GetHeight() const override { return m_data.height; };

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };
    void SetVSync(bool enabled) override 
    { 
        if (enabled) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }

        m_data.vsync = enabled;
    }
    bool IsVSync() const override { return m_data.vsync; }

    void* GetPlatformWindow() const override { return m_pWindow; }
    
private:
    std::unique_ptr<GraphicsContext> m_upContext;
    GLFWwindow* m_pWindow;

    struct WindowData
    {
        std::string title;
        std::uint32_t width;
        std::uint32_t height;
        bool vsync;

        EventCallbackFn EventCallback;
    };

    WindowData m_data;
};