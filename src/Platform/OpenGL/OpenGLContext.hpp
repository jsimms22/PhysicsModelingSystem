#pragma once

// vendor
// project header
#include "../../Renderer/GraphicsContext.hpp"
// std library
#include <memory>

struct GLFWwindow;

class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* handle)
        : m_pWindowHandle{handle} {}

    virtual ~OpenGLContext() = default;

    void Init() override;
    void SwapBuffers() override;
    
private:
    GLFWwindow* m_pWindowHandle;
};