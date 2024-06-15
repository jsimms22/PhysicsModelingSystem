// project headers
#include "../include/meshClass.hpp"

Mesh::Mesh(fs::path filename, bool instanced)
{
    std::vector<Vertexf> vertex_bin;
    // Load vertex data from file
    loadObject(filename, vertex_bin);
    this->vertices = vertex_bin;

    // Create our Vertex Buffer and Vertex Array Objects
    // Bind the Vertex Array Object first, 
    glGenVertexArrays(1, &(this->VAO));
    glBindVertexArray(this->VAO);
    // Then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenBuffers(1, &(this->VBO));
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * STRIDE * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

    /* TODO use elements */
    
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)0);
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)(3*sizeof(float)));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)(6*sizeof(float)));

    if (instanced) {
    //     // instanced Position
    //     glGenBuffers(1, &(this->positionVBO));
    //     glBindBuffer(GL_ARRAY_BUFFER, this->positionVBO);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * INSTANCE_STRIDE * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
    //     glEnableVertexAttribArray(3);
    //     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, INSTANCE_STRIDE * sizeof(float), (void*)0);
    //     glVertexAttribDivisor(3, 1);

    //     // instanced Velocity
    //     glGenBuffers(1, &(this->velocityVBO));
    //     glBindBuffer(GL_ARRAY_BUFFER, this->velocityVBO);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
    //     glEnableVertexAttribArray(4);
    //     glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    //     glVertexAttribDivisor(4, 1);
    }

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void processVertex(std::vector<Vertexf>& vertex_bin, 
                    std::vector<std::string>& vertexMarker, 
                    std::vector<vec3f>& v, 
                    std::vector<vec2f>& vt, 
                    std::vector<vec3f>& vn)
{
    Vertexf temp;
    size_t vertex_itr = stoi(vertexMarker[0]) - 1;
    size_t texture_itr = stoi(vertexMarker[1]) - 1;
    size_t normal_itr = stoi(vertexMarker[2]) - 1;

    temp.v = v[vertex_itr];
    temp.vn = vn[normal_itr];
    temp.vt = vt[texture_itr];
    vertex_bin.push_back(temp);
}

void loadObject(fs::path filename, std::vector<Vertexf>& vertex_bin)
{
    std::vector<vec3f> v, vn;
    std::vector<vec2f> vt;

    // size_t v_count, vt_count, vn_count, f_count;
    // v_count = vt_count = vn_count = f_count = 0;

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
                vec3f hold1;
                if(iss >> temp) { hold1.data[0] = std::stof(temp); }
                if(iss >> temp) { hold1.data[1] = std::stof(temp); }
                if(iss >> temp) { hold1.data[2] = std::stof(temp); }
                v.push_back(hold1);
                break;
            case 2: // first word = "vt"
                vec2f hold2;
                if(iss >> temp) { hold2.data[0] = std::stof(temp); }
                if(iss >> temp) { hold2.data[1] = std::stof(temp); }
                vt.push_back(hold2);
                break;
            case 3: // first word = "vn"
                vec3f hold3;
                if(iss >> temp) { hold3.data[0] = std::stof(temp); }
                if(iss >> temp) { hold3.data[1] = std::stof(temp); }
                if(iss >> temp) { hold3.data[2] = std::stof(temp); }
                vn.push_back(hold3);
                break;
            case 4: // first word = "f"
                std::vector<std::string> v1, v2, v3;
                if(iss >> temp) { v1 = splitString(temp, '/'); }
                if(iss >> temp) { v2 = splitString(temp, '/'); }
                if(iss >> temp) { v3 = splitString(temp, '/'); }

                processVertex(vertex_bin, v1, v, vt, vn);
                processVertex(vertex_bin, v2, v, vt, vn);
                processVertex(vertex_bin, v3, v, vt, vn);
                break;
        }
    }
    // std::cout << "Final counts: " << v_count << ", " << vt_count << ", " << vn_count << ", " << f_count << std::endl;
    // std::cout << "bin size: " << vertex_bin.size() << std::endl;
    file.close();
}