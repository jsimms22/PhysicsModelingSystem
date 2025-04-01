// vendor
// project header
#include "../Renderer/Renderer.hpp"
#include "../Scene/Model.hpp"
// std library

void Renderer::Clear()
{
    /* Clears back buffer before new buffer is drawn */
    //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& VAO, const ElementBuffer& EBO, const std::shared_ptr<Shader>& Shader) const
{
}

void Renderer::DrawModelMesh(std::shared_ptr<IModel> pModel)
{
    if (!pModel) { return; }

    pModel->Update();

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