#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Events/Event.hpp"
// std library
#include <functional>
#include <string>
#include <memory>

struct WindowProps
{
    uint32_t m_width;
    uint32_t m_height;
    std::string m_title;

    WindowProps(const std::string& title = "My Application",
                uint32_t width = 1200,
                uint32_t height = 1200)
        : m_width{width}, m_height{height}, m_title{title} {}
};

class IWindow
{
public:
    using EventCallbackFn = std::function<void>(Event&);

    virtual ~IWindow() = default;

    virtual void SwapBuffers() = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void UpdateWindowTitle(float dt, int numActive) = 0;
    // BAD
    virtual GLFWwindow* GetWindowPtr() = 0;

    virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;
    // Window attributes
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    static std::shared_ptr<IWindow> Create(const WindowProps& props = WindowProps());
};