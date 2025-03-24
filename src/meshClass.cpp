// project headers
#include "../include/meshClass.hpp"

Mesh::Mesh(std::vector<vertexf> _v, std::vector<unsigned int> _in/*, std::vector<Texture> _tex*/)
    : VAO{}
{
    this->vertices = _v;
    this->indices = _in;
    // this->textures = _tex;

    // Bind the Vertex Array Object first,
    this->VAO.Bind();
    // Then bind and set vertex buffer(s)
    VBObj VBO(this->vertices);
    // Generates Element Buffer Object and links it to indices
	EBObj EBO(this->indices);

    // Position
    VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(vertexf), (void*)0);
    // Normal
    VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertexf), (void*)(3*sizeof(float)));
    // Texture
    VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertexf), (void*)(6*sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    this->VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
   
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh::Mesh(fs::path filename, bool instanced)
    : VAO{}
{
    std::vector<vertexf> vertexBin;
    // Load vertex data from file
    LoadObject(filename, vertexBin);
    this->vertices = vertexBin;

    // Bind the Vertex Array Object first,
    this->VAO.Bind();
    // Then bind and set vertex buffer(s)
    VBObj VBO(this->vertices);
    // Generates Element Buffer Object and links it to indices
	EBObj EBO(this->indices);

    // Position
    VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(vertexf), (void*)0);
    // Normal
    VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(vertexf), (void*)(3*sizeof(float)));
    // Texture
    VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, sizeof(vertexf), (void*)(6*sizeof(float)));

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
    this->VAO.Unbind();
    VBO.Unbind();
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
    size_t vertItr = stoi(vertexMarker[0]) - 1;
    size_t texItr = stoi(vertexMarker[1]) - 1;
    size_t normItr = stoi(vertexMarker[2]) - 1;

    temp.v = v[vertItr];
    temp.vn = vn[normItr];
    temp.vt = vt[texItr];
    vertexBin.push_back(temp);
}

void LoadObject(fs::path filename, std::vector<vertexf>& vertexBin)
{
    std::vector<vec3f> v, vn;
    std::vector<vec2f> vt;

    size_t v_count, vt_count, vn_count, f_count;
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