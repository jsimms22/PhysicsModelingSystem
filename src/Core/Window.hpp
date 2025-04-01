#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Core/Mouse.hpp"
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

struct WindowProps
{
    int width = 1200;
    int height = 1200;
    const char* title = "My Application";
};

class Window
{
public:
    Window(WindowProps props);

    ~Window();

    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    // determine if user is attempting to close window
    void ProcessInput(Mouse& mouse);
    // Clear openGL error buffer
    void ClearErrors() const;
    // Calculate average FPS
    void DisplayStats(std::size_t& totalFrames, float& lastFrameTime, std::size_t numActive);
    // Update title bar
    void UpdateWindowTitle(float dt, int numActive);

    // BAD!
    GLFWwindow* GetWindowPtr() { return m_pWindow; }
    
private:
    std::unique_ptr<WindowContext> m_pContext;
    GLFWwindow* m_pWindow;
    WindowProps m_windowProps;
};