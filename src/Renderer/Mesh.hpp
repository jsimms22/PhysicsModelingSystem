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
#include <string>

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
class Mesh
{
public:
    // Constructors
    Mesh(std::vector<vertex> vertices, 
         int32_t instances = 1, 
         std::vector<mat4x4d> matrices = {}) 
        : m_vertices{vertices}, m_instanceCount{instances}, m_instanceMatrices{matrices} {}

    Mesh(const std::string& filename, 
         int32_t instances = 1, 
         std::vector<mat4x4d> matrices = {});

    Mesh(std::vector<vertex> vertices, 
         std::vector<std::uint32_t> indices, 
         std::vector<Texture> textures = {}, 
         int32_t instances = 1, 
         std::vector<mat4x4d> matrices = {});
    
    //void draw(Shader& shader, EditorCamera& camera);

    std::vector<vertex> m_vertices;
    std::vector<std::uint32_t> m_indices;
    std::vector<Texture> m_textures;
    
    int32_t m_instanceCount = 1;
    std::vector<mat4x4d> m_instanceMatrices;

    VertexArray m_VA0;

private:
     // Hash function for mapping specific strings to integers
     int HashString(const std::string& str);

     // Function to split a string based on a delimiter
     std::vector<std::string> SplitString(const std::string& str, char delimiter);

     void ProcessVertex(std::vector<vertex>& vertexBin, 
                         std::vector<std::string>& vertexMarker, 
                         std::vector<vec3d>& v, 
                         std::vector<vec2f>& vt, 
                         std::vector<vec3f>& vn);

     void LoadObject(const std::string& filename, std::vector<vertex>& vertexBin);
};