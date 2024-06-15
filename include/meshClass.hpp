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
constexpr int VERTEX_LIMIT {2000};

void processVertex(std::vector<Vertexf>& vertex_bin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn);

void loadObject(fs::path filename, std::vector<Vertexf>& vertex_bin);

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ r g b }{ tx1 tx2 }
class Mesh
{
public:
    std::vector<Vertexf> vertices;
    std::vector<unsigned int> indices;
    // std::vector<Texture> textures;
    unsigned int VAO;
    unsigned int VBO;
    // unsigned int positionVBO;
    // unsigned int velocityVBO;

    Mesh(std::vector<Vertexf> _v)
        : vertices{_v} { }
    Mesh(fs::path filename, bool instanced);
    Mesh(std::vector<Vertexf> _v, std::vector<unsigned int>& _in/*, std::vector<Texture> _tex*/)
        :vertices{_v}, indices{_in}/*, textures{_tex}*/ { }

    //void draw(Shader& shader, Camera& camera);
};