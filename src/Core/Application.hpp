#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Platform/Windows/WindowsWindow.hpp"
#include "../Events/Event.hpp"
// std library
#include <memory>
#include <cstdlib>

int main(int argc, char** argv);

class Application : public std::enable_shared_from_this<Application>
{
    struct Private{ explicit Private() = default; };
public:
    Application(Private p);

    std::shared_ptr<IWindow> GetWindow() { return m_pWindow; }
    GLFWwindow* GetGLFWwindow() { return m_pWindow->GetWindowPtr(); }

    void Close();

    static std::shared_ptr<Application> GetApplication()
    {
        // If we cannot return a valid s_intance, then 
        // we should not create a new application
        return s_instance.lock();
    }

private: // Methods
    static std::shared_ptr<Application> Create()
    {
        if (auto instance = s_instance.lock()) {
            return instance;
        } else {
            instance = std::make_shared<Application>(Private());
            s_instance = instance;
            return instance;
        }
    }

    void Run();
    bool OnWindowClose();
    bool OnWindowResize();
    void DisplayStats();

    void ProcessInput(Mouse& mouse);

    void ClearErrors() const;

private: // Members
    std::shared_ptr<IWindow> m_pWindow;
    bool m_bRunning = false;
    bool m_bMinimized = false;
    float m_fLastFrameTime = 0.0f;
    float m_deltaTime = 0.0f;
    // TODO: Need a better way to track stats
    std::size_t m_totalModels = 0;
    std::size_t m_totalFrames = 0;
    
    // Allows Application to participate in its own lifetime
    static std::weak_ptr<Application> s_instance;

private: // Friends
    friend int ::main(int argc, char** argv);
};