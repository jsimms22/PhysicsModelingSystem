#pragma once

// std library
#include <vector>
// project headers
#include "types/vertex.hpp"
#include "shaderClass.hpp"
#include "cameraClass.hpp"
#include "utility.hpp"

void ProcessVertex(std::vector<vertexf>& vertexBin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn);

void LoadObject(fs::path filename, std::vector<vertexf>& vertexBin);

class VBObj
{
public:
    // VBObj() { }
    // Generates a VBO and links it to a list of vertices 
    VBObj(std::vector<vertexf> vertices)
    {
        glGenBuffers(1, &(m_ID));
	    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(vertices.size() * sizeof(vertexf)), vertices.data(), GL_STATIC_DRAW);
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
    std::vector<vertexf> vertices;
    std::vector<unsigned int> indices;
    // std::vector<Texture> textures;
    // unsigned int VAO;
    // unsigned int VBO;
    VAObj VAO;
    // VBObj VBO;
    // unsigned int positionVBO;
    // unsigned int velocityVBO;

    Mesh(std::vector<vertexf> _v) : vertices{_v} { }
    Mesh(fs::path filename, bool instanced);
    Mesh(std::vector<vertexf> _v, std::vector<unsigned int> _in/*, std::vector<Texture> _tex*/);

    //void draw(Shader& shader, Camera& camera);
};