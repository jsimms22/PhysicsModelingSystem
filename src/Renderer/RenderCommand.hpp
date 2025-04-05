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

    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        s_renderAPI->SetViewport(x,y,width,height);
    }

private:
    static std::unique_ptr<RenderAPI> s_renderAPI;
};