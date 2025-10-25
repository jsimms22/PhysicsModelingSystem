// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "Mesh.hpp"

#include "ElementBuffer.hpp"
#include "VertexBuffer.hpp"
// std library
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

// Hash function for mapping specific strings to integers
int HashString(const std::string& str) 
{
    if (str == "v") return 1;
    if (str == "vt") return 2;
    if (str == "vn") return 3;
    if (str == "f") return 4;
    return 0;
}

// Function to split a string based on a delimiter
std::vector<std::string> SplitString(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) { tokens.push_back(token); }

    return tokens;
}

void ProcessVertex(std::vector<vertex>& vertexBin, 
                   std::vector<std::string>& vertexMarker, 
                   std::vector<vec3d>& v, 
                   std::vector<vec2f>& vt, 
                   std::vector<vec3f>& vn)
{
    vertex temp;
    std::size_t vertItr = stoull(vertexMarker[0]) - 1;
    std::size_t texItr = stoull(vertexMarker[1]) - 1;
    std::size_t normItr = stoull(vertexMarker[2]) - 1;

    temp.v = v[vertItr];
    temp.vn = vn[normItr];
    temp.vt = vt[texItr];
    vertexBin.push_back(temp);
}

void LoadObject(const std::string& filename, std::vector<vertex>& vertexBin)
{
    std::vector<vec3d> v;
    std::vector<vec3f> vn;
    std::vector<vec2f> vt;

    std::size_t v_count, vt_count, vn_count, f_count;
    v_count = vt_count = vn_count = f_count = 0;

    std::ifstream file(filename);
    if (!file) 
    {
        std::cout << "Error opening file: " << filename << std::endl; 
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        std::string firstWord, temp;
        iss >> firstWord;

        switch (HashString(firstWord)) 
        {
            case 1: // first word = "v"
            {
                vec3d holdv;
                if(iss >> temp) { holdv.data[0] = std::stod(temp); }
                if(iss >> temp) { holdv.data[1] = std::stod(temp); }
                if(iss >> temp) { holdv.data[2] = std::stod(temp); }
                v.push_back(holdv);
                ++v_count;
                break;
            }
            case 2: // first word = "vt"
            {
                vec2f holdvt;
                if(iss >> temp) { holdvt.data[0] = std::stof(temp); }
                if(iss >> temp) { holdvt.data[1] = std::stof(temp); }
                vt.push_back(holdvt);
                ++vt_count;
                break;
            }
            case 3: // first word = "vn"
            {
                vec3f holdvn;
                if(iss >> temp) { holdvn.data[0] = std::stof(temp); }
                if(iss >> temp) { holdvn.data[1] = std::stof(temp); }
                if(iss >> temp) { holdvn.data[2] = std::stof(temp); }
                vn.push_back(holdvn);
                ++vn_count;
                break;
            }
            case 4: // first word = "f"
            {
                std::vector<std::string> v1, v2, v3;
                if(iss >> temp) { v1 = SplitString(temp, '/'); }
                if(iss >> temp) { v2 = SplitString(temp, '/'); }
                if(iss >> temp) { v3 = SplitString(temp, '/'); }
                ProcessVertex(vertexBin, v1, v, vt, vn);
                ProcessVertex(vertexBin, v2, v, vt, vn);
                ProcessVertex(vertexBin, v3, v, vt, vn);
                ++f_count;
                break;
            }
        }
    }
    // std::cout << "Final counts: " << v_count << ", " << vt_count << ", " << vn_count << ", " << f_count << std::endl;
    // std::cout << "Vertex bin size: " << vertexBin.size() << std::endl;
    file.close();
}

//Mesh::Mesh(std::vector<vertex> vertices, std::int32_t instances /* = 1 */, std::vector<mat4x4d> matrices /* = {} */) 
//    : m_vertices{vertices}, m_instanceCount{instances}, m_instanceMatrices{matrices} {}

Mesh::Mesh(std::vector<vertex> vertices, std::vector<std::uint32_t> indices, std::vector<Texture> textures /* = {} */, std::int32_t instances /* = 1 */, std::vector<mat4x4d> matrices /* = {} */)
    : m_vertices{vertices}, m_indices{indices}, m_textures{textures}, m_instanceCount{instances}, m_instanceMatrices{matrices}
{
    // Bind the Vertex Array Object first,
    m_VAO.Bind();
    // Then bind and set vertex buffer(s)
    VertexBuffer instanceVBO(matrices);
    VertexBuffer VBO(m_vertices);
    // Generates Element Buffer Object and links it to indices
    ElementBuffer EBO(m_indices);

    // Position
    m_VAO.LinkAttribute(VBO, 0, 3, GL_DOUBLE, sizeof(vertex), reinterpret_cast<void*>(0));
    // Normal
    m_VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(3*sizeof(double)));
    // Texture
    m_VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(3*sizeof(float) + 3*sizeof(double)));
    // Color
    m_VAO.LinkAttribute(VBO, 3, 4, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(5*sizeof(float) + 3*sizeof(double)));

    if (m_instanceCount > 1) 
    {
        // Position
        m_VAO.LinkAttribute(instanceVBO, 4, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(0));
        // Normal
        m_VAO.LinkAttribute(instanceVBO, 5, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(1*sizeof(vec4d)));
        // Texture
        m_VAO.LinkAttribute(instanceVBO, 6, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(2*sizeof(vec4d)));
        // Color(?)
        m_VAO.LinkAttribute(instanceVBO, 7, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(3*sizeof(vec4d)));

        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);
    }

    // Unbind all to prevent accidentally modifying them
    m_VAO.Unbind();
    VBO.Unbind();
    instanceVBO.Unbind();
    EBO.Unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh::Mesh(const std::string& filename, std::int32_t instances /* = 1*/, std::vector<mat4x4d> matrices /* = {}*/)
    : m_instanceCount{instances}, m_instanceMatrices{matrices}
{
    // Load vertex data from file
    LoadObject(filename, m_vertices);

    // Bind the Vertex Array Object first,
    m_VAO.Bind();
    // Then bind and set vertex buffer(s)
    VertexBuffer instanceVBO(matrices);
    VertexBuffer VBO(m_vertices);
    // Generates Element Buffer Object and links it to indices
    ElementBuffer EBO(m_indices);

    // Position
    m_VAO.LinkAttribute(VBO, 0, 3, GL_DOUBLE, sizeof(vertex), reinterpret_cast<void*>(0));
    // Normal
    m_VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(3*sizeof(double)));
    // Texture
    m_VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(3*sizeof(float) + 3*sizeof(double)));
    // Color
    m_VAO.LinkAttribute(VBO, 3, 4, GL_FLOAT, sizeof(vertex), reinterpret_cast<void*>(5*sizeof(float) + 3*sizeof(double)));

    if (m_instanceCount > 1) 
    {
        // Position
        m_VAO.LinkAttribute(instanceVBO, 4, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(0));
        // Normal
        m_VAO.LinkAttribute(instanceVBO, 5, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(1*sizeof(vec4d)));
        // Texture
        m_VAO.LinkAttribute(instanceVBO, 6, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(2*sizeof(vec4d)));
        // Color(?)
        m_VAO.LinkAttribute(instanceVBO, 7, 4, GL_DOUBLE, sizeof(mat4x4d), reinterpret_cast<void*>(3*sizeof(vec4d)));

        // order, 2 -> use for 2 instances
        // order, 1 -> whole instance
        // order, 0 -> each vertex
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glVertexAttribDivisor(7, 1);
    }

    m_VAO.Unbind();
    VBO.Unbind();
    instanceVBO.Unbind();
    EBO.Unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}