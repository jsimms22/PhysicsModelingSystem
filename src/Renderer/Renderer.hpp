#pragma once

// vendor
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project header
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/ElementBuffer.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/RenderAPI.hpp"
// std library
#include <memory>

class IModel;

class Renderer
{
public:
    static void Init();

    static void Clear();

    static void OnWindowResize(uint32_t width, uint32_t height);

    static RenderAPI::API GetAPI();
    
    // LEGACY
    void DrawModelMesh(std::shared_ptr<IModel> pModel);
};