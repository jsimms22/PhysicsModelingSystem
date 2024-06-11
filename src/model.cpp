// project headers
#include "../include/model.hpp"

Modelf createModel(Meshf mesh)
{
    Modelf model;
    model.mesh = mesh;
    model.position = { 0,  0,  -0.5 };
    model.rotation = { 0,  0,   0 };
    model.scale = 1;
    model.renderMethod = GL_TRIANGLES;
    return model;
}

void destroyModel(Modelf model)
{
    destroyMesh(model.mesh);
}

void processVertex(std::vector<float>& vertex_bin, 
                    std::vector<std::string>& vertexData, 
                    std::array<Vertex3f, VERTEX_LIMIT>& v, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vt, 
                    std::array<Vertex3f, VERTEX_LIMIT>& vn)
{
    size_t vertex_itr = stoi(vertexData[0]) - 1;
    size_t texture_itr = stoi(vertexData[1]) - 1;
    size_t normal_itr = stoi(vertexData[2]) - 1;

    // std::cout << vertex_itr << ", " << texture_itr << ", " << normal_itr << std::endl;
    // { x, y, z, norm1, norm2, norm3, texture1, texture2 }
    vertex_bin.push_back(v[vertex_itr].position.data[0]); // x
    vertex_bin.push_back(v[vertex_itr].position.data[1]); // y
    vertex_bin.push_back(v[vertex_itr].position.data[2]); // z

    vertex_bin.push_back(vn[normal_itr].position.data[0]); // norm 1
    vertex_bin.push_back(vn[normal_itr].position.data[1]); // norm 2
    vertex_bin.push_back(vn[normal_itr].position.data[2]); // norm 3

    vertex_bin.push_back(vt[texture_itr].position.data[0]); // texture 1
    vertex_bin.push_back(vt[texture_itr].position.data[1]); // texture 2
}

void loadObject(std::string filename, std::vector<float>& vertex_bin)
{
    std::array<Vertex3f, VERTEX_LIMIT> v;
    std::array<Vertex3f, VERTEX_LIMIT> vt;
    std::array<Vertex3f, VERTEX_LIMIT> vn;

    size_t v_count = 0;
    size_t vt_count = 0;
    size_t vn_count = 0;
    size_t f_count = 0;

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl; 
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstword, temp;
        iss >> firstword;

        switch (hashString(firstword)) {
            case 1: // first word = "v"
                if(iss >> temp) { v[v_count].position.data[0] = std::stof(temp); }
                if(iss >> temp) { v[v_count].position.data[1] = std::stof(temp); }
                if(iss >> temp) { v[v_count].position.data[2] = std::stof(temp); }
                ++v_count;
                break;
            case 2: // first word = "vt"
                if(iss >> temp) { vt[vt_count].position.data[0] = std::stof(temp); }
                if(iss >> temp) { vt[vt_count].position.data[1] = std::stof(temp); }
                ++vt_count;
                break;
            case 3: // first word = "vn"
                if(iss >> temp) { vn[vn_count].position.data[0] = std::stof(temp); }
                if(iss >> temp) { vn[vn_count].position.data[1] = std::stof(temp); }
                if(iss >> temp) { vn[vn_count].position.data[2] = std::stof(temp); }
                // std::cout << "vn(" << vn_count << "}: " << vn[vn_count].position.data[0] << ", ";
                // std::cout << "vn(" << vn_count << "}: " << vn[vn_count].position.data[1] << ", ";
                // std::cout << "vn(" << vn_count << "}: " << vn[vn_count].position.data[2] << std::endl;
                ++vn_count;
                break;
            case 4: // first word = "f"
                std::vector<std::string> v1, v2, v3;
                if(iss >> temp) { v1 = splitString(temp, '/'); }
                if(iss >> temp) { v2 = splitString(temp, '/'); }
                if(iss >> temp) { v3 = splitString(temp, '/'); }

                processVertex(vertex_bin, v1, v, vt, vn);
                processVertex(vertex_bin, v2, v, vt, vn);
                processVertex(vertex_bin, v3, v, vt, vn);
                ++f_count;
                break;
        }
    }
    std::cout << "Final counts: " << v_count << ", " << vt_count << ", " << vn_count << ", " << f_count << std::endl;
    std::cout << "bin size: " << vertex_bin.size() << std::endl;
    file.close();
}

Meshf createMesh(std::string filename, bool instanced)
{
    std::vector<float> vertex_bin;
    loadObject(filename, vertex_bin);

    Meshf mesh;
    mesh.vertices = vertex_bin;
    mesh.numVertices = vertex_bin.size() / STRIDE;

    // Create our Vertex Buffer and Vertex Array Objects
    glGenVertexArrays(1, &(mesh.VAO));
    glBindVertexArray(mesh.VAO);

    glGenBuffers(1, &(mesh.VBO));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * STRIDE * mesh.numVertices, mesh.vertices.data(), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)0);
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)12);
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)24);

    if (instanced) {
        // Position
        glGenBuffers(1, &(mesh.positionVBO));
        glBindBuffer(GL_ARRAY_BUFFER, mesh.positionVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * INSTANCE_STRIDE * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, INSTANCE_STRIDE * sizeof(float), (void*)0);
        glVertexAttribDivisor(3, 1);

        // Velocity
        glGenBuffers(1, &(mesh.velocityVBO));
        glBindBuffer(GL_ARRAY_BUFFER, mesh.velocityVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
        glVertexAttribDivisor(4, 1);
    }

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return mesh;
}

void destroyMesh(Meshf mesh)
{
    glDeleteVertexArrays(1, &(mesh.VAO));
    glDeleteBuffers(1, &(mesh.VBO));
}