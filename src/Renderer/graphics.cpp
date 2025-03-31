// vendors
// project headers
#include "../Renderer/Graphics.hpp"
#include "../Renderer/Mesh.hpp"
// std library

std::vector<vertexf> FloorVertex(uint32_t vertexCount, float length, float width)
{
    float coord_x = -(width / 2);
    float coord_z = -(length / 2);
    float dx = (width / vertexCount);
    float dz = (length / vertexCount);
    std::vector<vertexf> floor;
    for (uint32_t i=0; i<vertexCount; ++i) {
        for (uint32_t j=0; j<vertexCount; ++j) {
            floor.push_back(vertexf
                {   //position
                    vec3f{ (coord_x + j*dx), 0.0f, (coord_z + i*dz) },
                    // normal
                    vec3f{ 1.0f, 1.0f, 1.0f },
                    // texture
                    vec2f{ 0.0f, 0.0f },
                    // color
                    vec4f{ 1.f, 1.f, 1.f, 1.f}
                });
        }
    }
    // std::cout << floor.size() << std::endl;
    return floor;
}

std::vector<uint32_t> FloorIndex(uint32_t vertexCount)
{
    std::vector<uint32_t> index;
    for (uint32_t i=0; i<vertexCount-1; ++i) {
        for (uint32_t j=0; j<vertexCount-1; ++j) {
            uint32_t tl = (i*vertexCount) + j;
            uint32_t tr = tl + 1;
            uint32_t bl = ((i+1)*vertexCount) + j;
            uint32_t br = bl + 1;
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

void DrawModelMesh(std::shared_ptr<IModel> pModel)
{
    if (!pModel) { return; }

    // Retrive 
    std::shared_ptr<Mesh> mesh = pModel->GetMesh();
    std::shared_ptr<Shader> shader = pModel->GetShader();
    uint32_t mode = pModel->GetRenderMethod();
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

    // TODO: offload normal scaling to here from the vertex shaders

    shader->SetUniform4fm("model", matrices.model);

    shader->Bind();
    mesh->m_VA0.Bind();
    if (1 == mesh->m_instanceCount) {
        if (mesh->m_indices.size() == 0) { 
            glDrawArrays(mode, 0, mesh->m_vertices.size()); 
        } else { 
            glDrawElements(mode, mesh->m_indices.size(), GL_UNSIGNED_INT, 0); 
        }
    } else {
        glDrawElementsInstanced(mode, mesh->m_indices.size(), GL_UNSIGNED_INT, 0, mesh->m_instanceCount); 
    }
    mesh->m_VA0.Unbind();
    shader->Unbind();
}