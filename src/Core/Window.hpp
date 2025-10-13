#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "../Events/Event.hpp"
// std library
#include <functional>
#include <string>
#include <memory>
#include <cstdint>

struct WindowProps
{
    std::uint32_t width;
    std::uint32_t height;
    std::string title;

    WindowProps(std::uint32_t _width = 1200,
                std::uint32_t _height = 1200,
                const std::string& _title = "My Application")
        : width{_width}, height{_height}, title{_title} {}
};

class IWindow
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~IWindow() = default;
    
    virtual void UpdateWindowTitle(double dt, int numActive) = 0;

    virtual void OnUpdate() = 0;

    virtual std::uint32_t GetWidth() const = 0;
	virtual std::uint32_t GetHeight() const = 0;

    // Window attributes
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual void* GetPlatformWindow() const = 0;

    static std::unique_ptr<IWindow> Create(const WindowProps& props = WindowProps());
};