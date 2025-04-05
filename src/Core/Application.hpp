#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Platform/Windows/WindowsWindow.hpp"

#include "../Events/Event.hpp"
#include "../Events/WindowEvents.hpp"
#include "../Events/ApplicationEvents.hpp"
// std library
#include <memory>
#include <cstdlib>

int main(int argc, char** argv);

class Application : public std::enable_shared_from_this<Application>
{
    struct Private{ explicit Private() = default; };
public:
    struct Statistics
    {
        float lastFrameTime = 0.0f;
        float deltaTime = 0.0f;
        uint32_t targetFPS = 144;
        // TODO: Need a better way to track stats
        std::size_t totalModels = 0;
        std::size_t totalFrames = 0;
    };

    // Private Constructor
    Application(Private p);

    static std::shared_ptr<Application> GetApplication()
    {
        // If we cannot return a valid instance, then 
        // we should not create a new application
        return s_applicationInstance.lock();
    }

    Statistics& GetStats() { return m_stats; }

    IWindow& GetWindow() { return *m_spWindow; }

    void Close() { m_bRunning = false; }
    void OnEvent(Event& e);

private: // Methods
    static std::shared_ptr<Application> Create();

    void Run();
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

    void DisplayStats();
    void ClearErrors() const;

private: // Members
    // Allows Application to participate in its own lifetime
    static std::weak_ptr<Application> s_applicationInstance;

    // Window(s)
    std::unique_ptr<IWindow> m_spWindow;
    bool m_bRunning = true;
    bool m_bMinimized = false;

    // Stats of App
    Statistics m_stats;

private: // Friends
    friend int ::main(int argc, char** argv);
};