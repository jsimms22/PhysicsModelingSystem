#pragma once

// vendors
// project headers
// std library
#include <cstdlib>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

class Event;

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
    
    virtual void UpdateWindowTitle(double dt, std::size_t numActive) = 0;

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