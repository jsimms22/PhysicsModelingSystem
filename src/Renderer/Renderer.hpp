#pragma once

// vendor
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project header
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/ElementBuffer.hpp"
#include "../Renderer/Shader.hpp"
// std library
#include <memory>

class IModel;

class Renderer
{
public:
    // Constructor
    Renderer() = default;

    // Destructor
    ~Renderer() = default;

    void Clear();
    
    void Draw(const VertexArray& VAO, const ElementBuffer& EBO, const std::shared_ptr<Shader>& Shader) const;
    
    void DrawModelMesh(std::shared_ptr<IModel> pModel);
};