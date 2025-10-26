// vendor
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project header
#include "OpenGLRenderAPI.hpp"
// std library

void OpenGLRenderAPI::Init()
{
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glPointSize(3.0f);
}

void OpenGLRenderAPI::SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height)
{
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void OpenGLRenderAPI::SetClearColor(const vec4f& color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
}

void OpenGLRenderAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}