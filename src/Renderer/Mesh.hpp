#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../types.hpp"
#include "../Renderer/VertexArray.hpp"
#include "../Renderer/ElementBuffer.hpp"
#include "../Renderer/Texture.hpp"
// std library
#include <vector>

void ProcessVertex(std::vector<vertexf>& vertexBin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn);

void LoadObject(const std::string& filename, std::vector<vertexf>& vertexBin);

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
class Mesh
{
public:
    // Constructors
    Mesh(std::vector<vertexf> vertices, 
         int32_t instances = 1, 
         std::vector<mat4x4f> matrices = {}) 
        : m_vertices{vertices}, m_instanceCount{instances}, m_instanceMatrices{matrices} {}

    Mesh(const std::string& filename, 
         int32_t instances = 1, 
         std::vector<mat4x4f> matrices = {});

    Mesh(std::vector<vertexf> vertices, 
         std::vector<uint32_t> indices, 
         std::vector<Texture> textures = {}, 
         int32_t instances = 1, 
         std::vector<mat4x4f> matrices = {});
    
    //void draw(Shader& shader, EditorCamera& camera);

    std::vector<vertexf> m_vertices;
    std::vector<uint32_t> m_indices;
    std::vector<Texture> m_textures;
    
    int32_t m_instanceCount = 1;
    std::vector<mat4x4f> m_instanceMatrices;

    VertexArray m_VA0;
};