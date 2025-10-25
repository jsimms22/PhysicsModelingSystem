// vendor
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project header
#include "Renderer.hpp"

#include "ElementBuffer.hpp"
#include "Mesh.hpp"
#include "RenderCommand.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

#include "../Scene/Model.hpp"
// std library
#include <cstdlib>
#include <cstdint>
#include <iostream>

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::Clear()
{
    RenderCommand::Clear();
}

void Renderer::OnWindowResize(const std::uint32_t width, const std::uint32_t height)
{
    
    RenderCommand::SetViewport(0, 0, width, height);
}

RenderAPI::API Renderer::GetAPI() 
{ 
    return RenderAPI::GetAPI(); 
}

Renderer::ModelData Renderer::DrawModelMesh(std::shared_ptr<IModel> pModel)
{
    Renderer::ModelData data;
    if (!pModel) { return data; }

    pModel->Update();

    const double scale = static_cast<double>(pModel->GetScale());
    const vec3d scaling{ scale, scale, scale };

    /* Position */
    data.position = mat4x4_translation<double>(data.position, pModel->GetPosition());
    /* Rotation */
    data.rotation = mat4_eulerAngles<double>(pModel->GetRotation());
    /* Scaling */
    data.scaling = mat4x4_buildScaler<double>(scaling);
    /* Model matrix */
    data.model = mat4x4_mul<double>(data.rotation, data.scaling);
    data.model = mat4x4_mul<double>(data.position, data.model);

#ifdef Debug
    std::cout << "POSITION:\n";
    std::cout << data.position << '\n';
    std::cout << "ROTATION:\n";
    std::cout << data.rotation << '\n';
    std::cout << "SCALING:\n";
    std::cout << data.scaling << '\n';
    std::cout << "MODEL:\n";
    std::cout << data.model << '\n';
#endif //Debug
    
    // TODO: offload normal scaling to here from the vertex shaders
    
    pModel->GetShader()->SetUniform4dm("model", data.model);

    pModel->GetShader()->Bind();
    pModel->GetMesh()->GetVAO()->Bind();
    if (1 == pModel->GetMesh()->GetNumInstances()) 
    {
        if (pModel->GetMesh()->GetIndices().size() == 0) 
        {
            glDrawArrays(pModel->GetRenderMethod(), 
                         0, 
                         static_cast<GLsizei>(pModel->GetMesh()->GetVertices().size())); 
        } 
        else 
        {
            glDrawElements(pModel->GetRenderMethod(), 
                           static_cast<GLsizei>(pModel->GetMesh()->GetIndices().size()), 
                           GL_UNSIGNED_INT, 
                           0); 
        }
    } 
    else 
    {
        glDrawElementsInstanced(pModel->GetRenderMethod(), 
                                static_cast<GLsizei>(pModel->GetMesh()->GetIndices().size()), 
                                GL_UNSIGNED_INT, 
                                0, 
                                pModel->GetMesh()->GetNumInstances()); 
    }
    
    pModel->GetMesh()->GetVAO()->Unbind();
    pModel->GetShader()->Unbind();

    return data;
}