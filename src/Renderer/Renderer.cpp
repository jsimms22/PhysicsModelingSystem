// vendor
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    glm::vec3 scaling{ scale, scale, scale };

    /* Position */
    data.position = glm::translate(glm::mat4x4(1.0), pModel->GetPosition());

    /* Rotation (Euler angles) */
    glm::vec3 rot = pModel->GetRotation();

    glm::mat4x4 rotX = glm::rotate(glm::mat4x4(1.0), rot.x, glm::vec3(1, 0, 0));
    glm::mat4x4 rotY = glm::rotate(glm::mat4x4(1.0), rot.y, glm::vec3(0, 1, 0));
    glm::mat4x4 rotZ = glm::rotate(glm::mat4x4(1.0), rot.z, glm::vec3(0, 0, 1));

    data.rotation = rotZ * rotY * rotX;

    /* Scaling */
    data.scaling = glm::scale(glm::mat4x4(1.0), scaling);

    /* Model matrix */
    data.model = data.rotation * data.scaling;
    data.model = data.position * data.model;

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