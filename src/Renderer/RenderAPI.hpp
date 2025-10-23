#pragma once

// vendor
// project header
#include "../types.hpp"
// std library
#include <memory>

class RenderAPI : public std::enable_shared_from_this<RenderAPI>
{
public:
    enum class API
    {
        None = 0,
        OpenGL = 1,
        DX11 = 2,
        DX12 = 3,
        Vulkan = 4
    };

    virtual ~RenderAPI() = default;
    
    static std::unique_ptr<RenderAPI> Create();

    static API GetAPI() { return s_API; }

    virtual void Init() = 0;
    virtual void SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height) = 0;
    virtual void SetClearColor(const vec4f& color) = 0;
    virtual void Clear() = 0;

private:
    static API s_API;
};