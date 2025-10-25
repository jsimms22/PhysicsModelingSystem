#pragma once

// vendor
// project header
#include "../../Renderer/RenderAPI.hpp"
// std library

class OpenGLRenderAPI : public RenderAPI
{
public:
    virtual ~OpenGLRenderAPI() = default;
    virtual void Init() override;
    virtual void SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height) override;
    virtual void SetClearColor(const vec4f& color) override;
    virtual void Clear() override;
};