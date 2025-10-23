#pragma once

// vendors
// project headers
#include "../Renderer/RenderAPI.hpp"
// std library

class RenderCommand
{
public:
    static void Init()
    {
        s_renderAPI->Init();
    }

    static void Clear()
    {
        s_renderAPI->Clear();
    }

    static void SetViewport(std::uint32_t x, std::uint32_t y, const std::uint32_t width, const std::uint32_t height)
    {
        s_renderAPI->SetViewport(x,y,width,height);
    }

private:
    static std::unique_ptr<RenderAPI> s_renderAPI;
};