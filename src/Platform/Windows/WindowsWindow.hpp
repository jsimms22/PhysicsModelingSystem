#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../../vendor/GL/include/glew.h"
#include "../../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../../Core/Mouse.hpp"
#include "../../Core/Window.hpp"
// std library
#include <iostream>
#include <memory>

class WindowContext
{
public:
    // Constructor
    WindowContext() = default;
    
    // Destructor
    ~WindowContext() { if (m_bInitialized) { glfwTerminate(); } }

    bool Initialize();

private:
    bool m_bInitialized = false;
};

class WindowsWindow : public IWindow
{
public:
    WindowsWindow(const WindowProps& props = WindowProps());

    ~WindowsWindow();

    void SwapBuffers() override;
    void PollEvents() override;
    bool ShouldClose() const override;
    // Update title bar
    void UpdateWindowTitle(float dt, int numActive) override;
    // BAD!
    GLFWwindow* GetWindowPtr() override { return m_pWindow; }

    uint32_t GetWidth() const override { return m_windowProps.m_width; };
	uint32_t GetHeight() const override { return m_windowProps.m_height; };
    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override {};
    void SetVSync(bool enabled) override {}
    bool IsVSync() const override {}
    
private:
    std::unique_ptr<WindowContext> m_pContext;
    GLFWwindow* m_pWindow;
    WindowProps m_windowProps;
};