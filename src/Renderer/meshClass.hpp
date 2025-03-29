#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../types.hpp"
// std library
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void ProcessVertex(std::vector<vertexf>& vertexBin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn);

void LoadObject(fs::path filename, std::vector<vertexf>& vertexBin);

class VBObj
{
public:
    VBObj() = delete;
    // Generates a VBO and links it to a list of vertices
    VBObj(std::vector<vertexf>& vertices)
    {
        glGenBuffers(1, &(m_ID));
	    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(vertices.size() * sizeof(vertexf)), vertices.data(), GL_STATIC_DRAW);
    }
    VBObj(std::vector<mat4x4f>& matrices)
    {
        glGenBuffers(1, &(m_ID));
	    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(matrices.size() * sizeof(mat4x4f)), matrices.data(), GL_STATIC_DRAW);
    }
    void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
    void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void Destroy() { glDeleteBuffers(1, &(m_ID));}
    unsigned int GetID() const { return m_ID; }
    
private:
    unsigned int m_ID;
};

class VAObj
{
public:
    VAObj() { glGenVertexArrays(1, &(m_ID)); }
    // Links a VBO attribute 
    void LinkAttribute(VBObj& VBO, unsigned int order, int layout, 
                    unsigned int type, int stride, void* offset)
    {
        VBO.Bind();
        glVertexAttribPointer(order, layout, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(order);
        VBO.Unbind();
    }
    void Bind() { glBindVertexArray(m_ID); }
    void Unbind() { glBindVertexArray(0); }
    void Destroy() { glDeleteVertexArrays(1, &(m_ID)); }
    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID;
};

class EBObj
{
public:
    EBObj() = delete; 
    EBObj(std::vector<unsigned int> indices) 
    { 
        glGenBuffers(1, &(m_ID));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);
    }
    void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
    void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
    void Destroy() { glDeleteBuffers(1, &(m_ID)); }
    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID;
};

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ r g b }{ tx1 tx2 }
class Mesh
{
public:
    std::vector<vertexf> m_vertices;
    std::vector<unsigned int> m_indices;
    // std::vector<Texture> m_textures;
    unsigned int m_instanceCount = 1;
    std::vector<mat4x4f> m_instanceMatrices;
    VAObj m_VA0;

    Mesh(std::vector<vertexf> vertices, unsigned int instances = 1U, std::vector<mat4x4f> matrices = {}) 
        : m_vertices{vertices}, m_instanceCount{instances}, m_instanceMatrices{matrices} {}
    Mesh(fs::path filename, unsigned int instances = 1U, std::vector<mat4x4f> matrices = {});
    Mesh(std::vector<vertexf> vertices, std::vector<unsigned int> indices/*, std::vector<Texture> _tex*/, unsigned int instances = 1, std::vector<mat4x4f> matrices = {});

    //void draw(Shader& shader, Camera& camera);
};