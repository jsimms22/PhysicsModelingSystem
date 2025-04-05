#pragma once

// vendor
#define GLFW_INCLUDE_NONE
#include "../../../vendor/GL/include/glew.h"
#include "../../../vendor/GLFW/include/glfw3.h"
// project header
#include "../../Renderer/RenderAPI.hpp"
// std library
#include <memory>

class OpenGLRenderAPI : public RenderAPI
{
public:
    virtual void Init() override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void SetClearColor(const vec4f& color) override;
    virtual void Clear() override;
};