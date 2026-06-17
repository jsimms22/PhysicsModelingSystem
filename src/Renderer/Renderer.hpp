#pragma once

// vendor
#include <glm/mat4x4.hpp>
// project header
#include "RenderAPI.hpp"
// std library
#include <cstdint>
#include <memory>

class IModel;

class Renderer
{
public:
    struct ModelData 
    {
        glm::mat4x4 position;
        glm::mat4x4 rotation;
        glm::mat4x4 scaling;
        glm::mat4x4 model;
    };

    static void Init();

    static void Clear();

    static void OnWindowResize(std::uint32_t width, std::uint32_t height);

    static RenderAPI::API GetAPI();
    
    // LEGACY
    ModelData DrawModelMesh(std::shared_ptr<IModel> pModel);
};