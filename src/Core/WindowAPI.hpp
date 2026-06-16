#pragma once

// vendor
// project header
#include "../types.hpp"
// std library
#include <memory>

class WindowAPI : public std::enable_shared_from_this<WindowAPI>
{
public:
    enum class API
    {
        None = 0,
        GLFW = 1,
        QT6 = 2
    };

    virtual ~WindowAPI() = default;
    static API GetAPI() { return s_API; }

private:
    static API s_API;
};