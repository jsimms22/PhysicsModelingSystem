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
    void ProcessInput();

    // BAD!
    GLFWwindow* GetWindowPtr() { return m_pWindow; }
    
private:
    GLFWwindow* m_pWindow;
};

class Mouse
{
private:
    double xpos;
    double ypos;
    double pxpos;
    double pypos;
public:
    Mouse() : xpos{0.0}, ypos{0.0}, pxpos{0.0}, pypos{0.0} { }
    void UpdateMouse(GLFWwindow* _window, double xx, double yy)
    {
        pxpos = xx;
        pypos = yy;
        glfwGetCursorPos(_window, &xx, &yy);
    }
    double GetX() const { return xpos; }
    double GetY() const { return ypos; }
    double GetDX() const { return xpos - pxpos; }
    double GetDY() const { return ypos - pypos; }
};