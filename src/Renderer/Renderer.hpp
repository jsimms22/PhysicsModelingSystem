#pragma once

// vendor
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
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
    struct ModelData 
    {
        mat4x4d position;
        mat4x4d rotation;
        mat4x4d scaling;
        mat4x4d model;
    };

    static void Init();

    static void Clear();

    static void OnWindowResize(std::uint32_t width, std::uint32_t height);

    static RenderAPI::API GetAPI();
    
    // LEGACY
    ModelData DrawModelMesh(std::shared_ptr<IModel> pModel);
};