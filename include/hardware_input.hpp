#pragma once

// std library
#include <iostream>
#include <memory>

// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

class GLFWContext
{
public:
    // Constructor
    GLFWContext() = default;
    
    // Destructor
    ~GLFWContext() { if (m_bInitialized) { glfwTerminate(); } }

    bool Initialize();

private:
    bool m_bInitialized = false;
};

class Window
{
public:
    Window(const std::unique_ptr<GLFWContext>& context, int width, int height, const char* title);

    ~Window();

    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    // determine if user is attempting to close window
    void ProcessInput();
    // Clear openGL error buffer
    void ClearErrors() const;
    // Calculate average FPS
    void DisplayStats(std::size_t& totalFrames, float& lastFrameTime, std::size_t numActive);
    // Update title bar
    void UpdateWindowTitle(float dt, int numActive);

    // BAD!
    GLFWwindow* GetWindowPtr() { return m_pWindow; }
    
private:
    GLFWwindow* m_pWindow;
};

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