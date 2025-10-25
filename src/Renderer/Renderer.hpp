#pragma once

// vendor
// project header
#include "RenderAPI.hpp"

#include "../Types/mat4x4.hpp"
// std library
#include <cstdint>
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