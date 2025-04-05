// vendors
// project headers
#include "../Renderer/GraphicsContext.hpp"
#include "../Platform/OpenGL/OpenGLContext.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/RenderAPI.hpp"
// std library
#include <iostream>

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (Renderer::GetAPI())
    {
        case RenderAPI::API::None:    std::cerr << "RendererAPI::None is currently not supported!\n"; return nullptr;
        case RenderAPI::API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
        case RenderAPI::API::DX11:    std::cerr << "RendererAPI::DX11 is currently not supported!\n"; return nullptr;
        case RenderAPI::API::DX12:    std::cerr << "RendererAPI::DX12 is currently not supported!\n"; return nullptr;
        case RenderAPI::API::Vulkan:  std::cerr << "RendererAPI::Vulkan is currently not supported!\n"; return nullptr;
    }

    std::cerr << "Unknown RendererAPI!\n";
    return nullptr;
}