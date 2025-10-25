#pragma once

// vendors
// project headers
// std library
#include <cstdlib>
#include <cstdint>
#include <memory>

class IWindow;
class Event;
class WindowCloseEvent;
class WindowResizeEvent;

int main(int /*argc*/, char** /*argv*/);

class Application
{
    struct Private{ explicit Private() = default; };

    struct Statistics
    {
        double lastFrameTime = 0.0;
        double deltaTime = 0.0;
        std::uint32_t targetFPS = 144;
        std::size_t totalModels = 0;
        std::size_t totalFrames = 0;
    };

public:
    // Private Constructor
    explicit Application(Private /*p*/);

    static std::shared_ptr<Application> GetApplication();

    Statistics& GetStats();

    IWindow& GetWindow();

    void Close();
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