#pragma once

// std library
#include <vector>
// project headers
#include "types/vertex.hpp"
#include "shaderClass.hpp"
#include "cameraClass.hpp"
#include "utility.hpp"

constexpr int STRIDE {8};
constexpr int INSTANCE_STRIDE {3};
constexpr int MAX_INSTANCES {20000};
// constexpr int VERTEX_LIMIT {2000};

void processVertex(std::vector<vertexf>& vertexBin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn);

void loadObject(fs::path filename, std::vector<vertexf>& vertexBin);

class VBObj
{
public:
    unsigned int ID;
    
    // VBObj() { }
    // Generates a VBO and links it to a list of vertices 
    VBObj(std::vector<vertexf> vertices)
    {
        glGenBuffers(1, &(this->ID));
	    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertexf), vertices.data(), GL_STATIC_DRAW);
    }
    void bind() { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
    void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void destroy() { glDeleteBuffers(1, &(this->ID));}
};

class VAObj
{
public:
    unsigned int ID;
    
    VAObj() { glGenVertexArrays(1, &(this->ID)); }
    // Links a VBO attribute 
    void linkAttrib(VBObj& VBO, unsigned int order, unsigned int layout, 
                    GLenum type, GLsizeiptr stride, void* offset)
    {
        VBO.bind();
        glVertexAttribPointer(order, layout, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(order);
        VBO.unbind();
    }
    void bind() { glBindVertexArray(this->ID); }
    void unbind() { glBindVertexArray(0); }
    void destroy() { glDeleteVertexArrays(1, &(this->ID)); }
};

class EBObj
{
public:
    unsigned int ID;
    
    EBObj(std::vector<unsigned int> indices) 
    { 
        glGenBuffers(1, &(this->ID));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
    void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }
    void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
    void destroy() { glDeleteBuffers(1, &(this->ID)); }
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

    Mesh(std::vector<vertexf> _v)
        : vertices{_v} { }
    Mesh(fs::path filename, bool instanced);
    Mesh(std::vector<vertexf> _v, std::vector<unsigned int> _in/*, std::vector<Texture> _tex*/);

    //void draw(Shader& shader, Camera& camera);
};