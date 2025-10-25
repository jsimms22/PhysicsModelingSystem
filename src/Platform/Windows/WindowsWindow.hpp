#pragma once

// vendors
// project headers
#include "../../Core/Window.hpp"
// std library
#include <cstdlib>
#include <memory>

class GraphicsContext;
class GLFWwindow;

class WindowsWindow : public IWindow
{
    struct WindowData
    {
        std::string title = "Window";
        std::uint32_t width = 0;
        std::uint32_t height = 0;
        bool vsync = false;
        EventCallbackFn EventCallback = nullptr;
    };

public:
    WindowsWindow(const WindowProps& props = WindowProps());

    ~WindowsWindow();

    // Update title bar
    void UpdateWindowTitle(double dt, std::size_t numActive) override;
    void OnUpdate() override;

    std::uint32_t GetWidth() const override { return m_data.width; };
	std::uint32_t GetHeight() const override { return m_data.height; };

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; };
    void SetVSync(bool enabled) override;
    bool IsVSync() const override { return m_data.vsync; }
    void* GetPlatformWindow() const override { return m_pWindow; }
    
private:
    std::unique_ptr<GraphicsContext> m_upContext;
    GLFWwindow* m_pWindow;
    WindowData m_data;
};