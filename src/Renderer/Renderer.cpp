// vendor
// project header
#include "../Renderer/RenderCommand.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scene/Model.hpp"
// std library

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::Clear()
{
    RenderCommand::Clear();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    
    RenderCommand::SetViewport(0, 0, width, height);
}

RenderAPI::API Renderer::GetAPI() 
{ 
    return RenderAPI::GetAPI(); 
}

void Renderer::DrawModelMesh(std::shared_ptr<IModel> pModel)
{
    if (!pModel) { return; }

    pModel->Update();

    // Retrive 
    std::shared_ptr<Mesh> mesh = pModel->GetMesh();
    std::shared_ptr<Shader> shader = pModel->GetShader();
    uint32_t mode = pModel->GetRenderMethod();
    vec3d position = pModel->GetPosition();
    vec3d rotation = pModel->GetRotation();
    double scale = static_cast<double>(pModel->GetScale());

    vec3d scaling{ scale, scale, scale };

    struct {
        mat4x4d position;
        mat4x4d rotation;
        mat4x4d scaling;
        mat4x4d model;
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

    shader->SetUniform4dm("model", matrices.model);

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