// vendors
// project headers
#include "../Renderer/meshClass.hpp"
#include "../Utils/utility.hpp"
// std library
#include <fstream>
#include <iostream>

Mesh::Mesh(std::vector<vertexf> vertices, std::vector<unsigned int> indices/*, std::vector<Texture> textures*/, unsigned int instances /* = 1U*/, std::vector<mat4x4f> matrices /* = {}*/)
    : m_vertices{vertices}, m_indices{indices}, /*m_textures{textures},*/ m_instanceCount{instances}, m_instanceMatrices{matrices}
{
    // Bind the Vertex Array Object first,
    m_VA0.Bind();
    // Then bind and set vertex buffer(s)
    VBObj instanceVBO(matrices);
    VBObj VBO(m_vertices);
    // Generates Element Buffer Object and links it to indices
    EBObj EBO(m_indices);

    // Position
    m_VA0.LinkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(0));
    // Normal
    m_VA0.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(3*sizeof(float)));
    // Texture
    m_VA0.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(6*sizeof(float)));

    if (m_instanceCount > 1U) {
        // Position
        m_VA0.LinkAttribute(instanceVBO, 3, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(0));
        // Normal
        m_VA0.LinkAttribute(instanceVBO, 4, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(1*sizeof(vec4f)));
        // Texture
        m_VA0.LinkAttribute(instanceVBO, 5, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(2*sizeof(vec4f)));
        // Color(?)
        m_VA0.LinkAttribute(instanceVBO, 6, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(3*sizeof(vec4f)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
    }

    // Unbind all to prevent accidentally modifying them
    m_VA0.Unbind();
    VBO.Unbind();
    instanceVBO.Unbind();
    EBO.Unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh::Mesh(fs::path filename, unsigned int instances /* = 1U*/, std::vector<mat4x4f> matrices /* = {}*/)
    : m_instanceCount{instances}, m_instanceMatrices{matrices}
{
    // Load vertex data from file
    LoadObject(filename, m_vertices);

    // Bind the Vertex Array Object first,
    m_VA0.Bind();
    // Then bind and set vertex buffer(s)
    VBObj instanceVBO(matrices);
    VBObj VBO(m_vertices);
    // Generates Element Buffer Object and links it to indices
    EBObj EBO(m_indices);

    // Position
    m_VA0.LinkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(0));
    // Normal
    m_VA0.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(3*sizeof(float)));
    // Texture
    m_VA0.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertexf), reinterpret_cast<void*>(6*sizeof(float)));

    if (m_instanceCount > 1U) {
        // Position
        m_VA0.LinkAttribute(instanceVBO, 3, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(0));
        // Normal
        m_VA0.LinkAttribute(instanceVBO, 4, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(1*sizeof(vec4f)));
        // Texture
        m_VA0.LinkAttribute(instanceVBO, 5, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(2*sizeof(vec4f)));
        // Color(?)
        m_VA0.LinkAttribute(instanceVBO, 6, 4, GL_FLOAT, sizeof(mat4x4f), reinterpret_cast<void*>(3*sizeof(vec4f)));

        // order, 2 -> use for 2 instances
        // order, 1 -> whole instance
        // order, 0 -> each vertex
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
    }

    m_VA0.Unbind();
    VBO.Unbind();
    instanceVBO.Unbind();
    EBO.Unbind();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ProcessVertex(std::vector<vertexf>& vertexBin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn)
{
    vertexf temp;
    std::size_t vertItr = stoull(vertexMarker[0]) - 1;
    std::size_t texItr = stoull(vertexMarker[1]) - 1;
    std::size_t normItr = stoull(vertexMarker[2]) - 1;

    temp.v = v[vertItr];
    temp.vn = vn[normItr];
    temp.vt = vt[texItr];
    vertexBin.push_back(temp);
}

void LoadObject(fs::path filename, std::vector<vertexf>& vertexBin)
{
    std::vector<vec3f> v, vn;
    std::vector<vec2f> vt;

    std::size_t v_count, vt_count, vn_count, f_count;
    v_count = vt_count = vn_count = f_count = 0;

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl; 
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstWord, temp;
        iss >> firstWord;

        switch (HashString(firstWord)) {
            case 1: // first word = "v"
                vec3f holdv;
                if(iss >> temp) { holdv.data[0] = std::stof(temp); }
                if(iss >> temp) { holdv.data[1] = std::stof(temp); }
                if(iss >> temp) { holdv.data[2] = std::stof(temp); }
                v.push_back(holdv);
                ++v_count;
                break;
            case 2: // first word = "vt"
                vec2f holdvt;
                if(iss >> temp) { holdvt.data[0] = std::stof(temp); }
                if(iss >> temp) { holdvt.data[1] = std::stof(temp); }
                vt.push_back(holdvt);
                ++vt_count;
                break;
            case 3: // first word = "vn"
                vec3f holdvn;
                if(iss >> temp) { holdvn.data[0] = std::stof(temp); }
                if(iss >> temp) { holdvn.data[1] = std::stof(temp); }
                if(iss >> temp) { holdvn.data[2] = std::stof(temp); }
                vn.push_back(holdvn);
                ++vn_count;
                break;
            case 4: // first word = "f"
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
    // std::cout << "Final counts: " << v_count << ", " << vt_count << ", " << vn_count << ", " << f_count << std::endl;
    // std::cout << "Vertex bin size: " << vertexBin.size() << std::endl;
    file.close();
}