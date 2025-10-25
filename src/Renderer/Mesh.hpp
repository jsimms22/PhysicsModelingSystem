#pragma once

// vendors
// project headers
#include "Texture.hpp"
#include "VertexArray.hpp"

#include "../Types/mat4x4.hpp"
#include "../Types/vertex.hpp"
// std library
#include <cstdint>
#include <string>
#include <vector>

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
class Mesh
{
public:
    // Constructors
     Mesh(std::vector<vertex> vertices, 
          std::int32_t instances = 1, 
          std::vector<mat4x4d> matrices = {});
     Mesh(const std::string& filename, 
          std::int32_t instances = 1, 
          std::vector<mat4x4d> matrices = {});
     Mesh(std::vector<vertex> vertices, 
          std::vector<std::uint32_t> indices, 
          std::vector<Texture> textures = {}, 
          std::int32_t instances = 1, 
          std::vector<mat4x4d> matrices = {});
    
     //void draw(Shader& shader, EditorCamera& camera);
     VertexArray* GetVAO() { return &m_VAO; }
     
     std::vector<vertex> GetVertices() const { return m_vertices; }
     std::vector<std::uint32_t> GetIndices() const { return m_indices; }
     std::vector<Texture> GetTextures() const { return m_textures; }

     std::int32_t GetNumInstances() const { return m_instanceCount; }
     std::vector<mat4x4d> GetMatrix() const { return m_instanceMatrices; }
     
private:
     VertexArray m_VAO;
     std::vector<vertex> m_vertices;
     std::vector<std::uint32_t> m_indices;
     std::vector<Texture> m_textures;

     std::int32_t m_instanceCount = 1;
     std::vector<mat4x4d> m_instanceMatrices;
};