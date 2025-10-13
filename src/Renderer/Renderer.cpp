// vendor
// project header
#include "../Renderer/RenderCommand.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scene/Model.hpp"
// std library
#include <iostream>

struct ModelData 
{
    mat4x4d position;
    mat4x4d rotation;
    mat4x4d scaling;
    mat4x4d model;
};

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::Clear()
{
    RenderCommand::Clear();
}

void Renderer::OnWindowResize(std::uint32_t width, std::uint32_t height)
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
    const std::uint32_t mode = pModel->GetRenderMethod();
    const vec3d position = pModel->GetPosition();
    const vec3d rotation = pModel->GetRotation();
    const double scale = static_cast<double>(pModel->GetScale());
    const vec3d scaling{ scale, scale, scale };

    ModelData data;
    /* Position */
    data.position = mat4x4_translation<double>(data.position, position);

    /* Rotation */
    data.rotation = mat4_eulerAngles<double>(rotation);

    /* Scaling */
    data.scaling = mat4x4_buildScaler<double>(scaling);

    /* Model matrix */
    data.model = mat4x4_mul<double>(data.rotation, data.scaling);
    data.model = mat4x4_mul<double>(data.position, data.model);

#ifdef DEBUG
    std::cout << "POSITION:\n";
    std::cout << data.position << '\n';
    std::cout << "ROTATION:\n";
    std::cout << data.rotation << '\n';
    std::cout << "SCALING:\n";
    std::cout << data.scaling << '\n';
    std::cout << "MODEL:\n";
    std::cout << data.model << '\n';
#endif //DEBUG

    // TODO: offload normal scaling to here from the vertex shaders
    
    shader->SetUniform4dm("model", data.model);

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