// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Core/windowClass.hpp"
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

    void Close();

    std::shared_ptr<Application> Get() { return m_pInstance.lock(); }

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
    std::weak_ptr<Application> m_pInstance;

private: // Friends
    friend int ::main(int argc, char** argv);
};