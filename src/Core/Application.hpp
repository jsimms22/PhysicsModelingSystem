// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Core/Window.hpp"
// std library
#include <memory>
#include <cstdlib>

int main(int argc, char** argv);

class Application : public std::enable_shared_from_this<Application>
{
public:
    Application();
    ~Application() = default;

    Window* GetWindow() { return m_pWindow.get(); }
    GLFWwindow* GetGLFWwindow() { return m_pWindow->GetWindowPtr(); }

    void Close();

    static std::shared_ptr<Application> GetApplication() 
    {
        if (auto instance = s_instance.lock())
        {
            return instance;
        }
        else
        {
            auto newInstance = std::make_shared<Application>();
            s_instance = newInstance;  // Ensure instance is set only once
            return newInstance;
        }
    }

private: // Methods
    void Run();
    bool OnWindowClose();
    bool OnWindowResize();

private: // Members
    std::unique_ptr<Window> m_pWindow;
    bool m_bRunning = false;
    bool m_bMinimized = false;
    float m_fLastFrameTime = 0.0f;
    // TODO: Need a better way to track stats
    std::size_t m_totalModels = 0;
    std::size_t m_totalFrames = 0;
    
    // Allows Application to participate in its own lifetime
    static std::weak_ptr<Application> s_instance;

private: // Friends
    friend int ::main(int argc, char** argv);
};