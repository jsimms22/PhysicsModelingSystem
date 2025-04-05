// vendor
// project header
#include "../OpenGL/OpenGLRenderAPI.hpp"
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
    //glPointSize(3.0f);
}

void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

void OpenGLRenderAPI::SetClearColor(const vec4f& color)
{
    //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClearColor(color[0], color[1], color[2], color[3]);
}

void OpenGLRenderAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}