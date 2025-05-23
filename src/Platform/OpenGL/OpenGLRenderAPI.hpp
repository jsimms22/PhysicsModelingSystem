#pragma once

// vendor
#define GLFW_INCLUDE_NONE
#include "GL/glew.h"
#include "GLFW/glfw3.h"
// project header
#include "../../Renderer/RenderAPI.hpp"
// std library
#include <memory>

class OpenGLRenderAPI : public RenderAPI
{
public:
    virtual ~OpenGLRenderAPI() = default;
    virtual void Init() override;
    virtual void SetViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) override;
    virtual void SetClearColor(const vec4f& color) override;
    virtual void Clear() override;
};