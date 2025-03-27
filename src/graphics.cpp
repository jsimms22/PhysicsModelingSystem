// project headers
#include "../include/graphics.hpp"

std::vector<vertexf> FloorVertex(unsigned int vertexCount, float length, float width)
{
    float coord_x = -(width / 2);
    float coord_z = -(length / 2);
    float dx = (width / vertexCount);
    float dz = (length / vertexCount);
    std::vector<vertexf> floor;
    for (unsigned int i=0; i<vertexCount; ++i) {
        for (unsigned int j=0; j<vertexCount; ++j) {
            floor.push_back(vertexf
                {   //position
                    vec3f{ (coord_x + j*dx), 0.0f, (coord_z + i*dz) },
                    // normal
                    vec3f{ 1.0f, 1.0f, 1.0f },
                    // texture
                    vec2f{ 0.0f, 0.0f }
                });
        }
    }
    // std::cout << floor.size() << std::endl;
    return floor;
}

std::vector<unsigned int> FloorIndex(unsigned int vertexCount)
{
    std::vector<unsigned int> index;
    for (unsigned int i=0; i<vertexCount-1; ++i) {
        for (unsigned int j=0; j<vertexCount-1; ++j) {
            unsigned int tl = (i*vertexCount) + j;
            unsigned int tr = tl + 1;
            unsigned int bl = ((i+1)*vertexCount) + j;
            unsigned int br = bl + 1;
            index.push_back(tl); index.push_back(bl); index.push_back(tr);
            index.push_back(tr); index.push_back(bl); index.push_back(br);
        }
    }
    // std::cout << index.size() << std::endl;
    // for (int i=0; i<(index.size()-2); i+=3) {
    //     std::cout << index[i] << "/" << index[i+1] << "/" << index[i+2] << std::endl;
    // }
    return index;
}

void DrawModelMesh(std::shared_ptr<BaseModel> pModel, bool bInstanced)
{
    if (!pModel) { return; }

    // Retrive 
    std::shared_ptr<Mesh> mesh = pModel->GetMesh();
    std::shared_ptr<Shader> shader = pModel->GetShader();
    unsigned int mode = pModel->GetRenderMethod();
    vec3f position = pModel->GetPosition();
    vec3f rotation = pModel->GetRotation();
    float scale = pModel->GetScale();

    vec3f scaling{ scale, scale, scale };

    struct {
        mat4x4f position;
        mat4x4f rotation;
        mat4x4f scaling;
        mat4x4f model;
    } matrices;

    /* Position */
    mat4x4_id(matrices.position);
    mat4x4_translation(matrices.position, matrices.position, position);

    /* Rotation */
    mat4x4_id(matrices.rotation);
    mat4_eulerAngles(matrices.rotation, rotation);

    /* Scaling */
    mat4x4_id(matrices.scaling);
    mat4x4_buildScaler(matrices.scaling, matrices.scaling, scaling);

    /* Model matrix */
    mat4x4_mul(matrices.model, matrices.rotation, matrices.scaling);
    mat4x4_mul(matrices.model, matrices.position, matrices.model);
    
    shader->Attach();

    if (!bInstanced) {
        glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "model"), 1, GL_FALSE, matrices.model.data->data);

        mesh->VAO.Bind();

        if (mesh->indices.size() == 0) { 
            glDrawArrays(mode, 0, mesh->vertices.size()); 
        } else { 
            glDrawElements(mode, mesh->indices.size(), GL_UNSIGNED_INT, 0); 
        }
    } else {

    }

    shader->Detach();
    mesh->VAO.Unbind();
}

// void drawInstanced(Mesh& mesh, unsigned int shaderID, unsigned int mode, int num, float scale)
// {
//     glUseProgram(shaderID);
//     glUniform1f(glGetUniformLocation(shaderID, "scale"), scale);

//     glBindVertexArray(mesh.VAO.ID);
//     glDrawArraysInstanced(mode, 0, mesh.vertices.size(), num);
//     glUseProgram(0);
//     glBindVertexArray(0);
// }