// vendor
// project header
#include "../Renderer/RenderAPI.hpp"
#include "../Platform/OpenGL/OpenGLRenderAPI.hpp"
// std library
#include <iostream>

RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

std::unique_ptr<RenderAPI> RenderAPI::Create()
{
    switch (s_API)
    {
        case RenderAPI::API::None:    std::cerr << "RendererAPI::None is currently not supported!\n"; return nullptr;
        case RenderAPI::API::OpenGL:  return std::make_unique<OpenGLRenderAPI>();
        case RenderAPI::API::DX11:    std::cerr << "RendererAPI::None is currently not supported!\n"; return nullptr;
        case RenderAPI::API::DX12:    std::cerr << "RendererAPI::None is currently not supported!\n"; return nullptr;
        case RenderAPI::API::Vulkan:  std::cerr << "RendererAPI::None is currently not supported!\n"; return nullptr;
    }

    return nullptr;
}