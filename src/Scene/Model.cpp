// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
#include <tinyxml2.h>
#pragma GCC diagnostic pop
// project headers
#include "../Scene/Model.hpp"
// std library

bool BaseModel::WriteAttributes()
{
    //std::shared_ptr<Mesh> m_modelMesh;
    //std::shared_ptr<Shader> m_modelShader;
    //vec3d m_position = {0.0, 0.0, 0.0};
    //vec3d m_rotation = {0.0, 0.0, 0.0};
    //float m_scale = 1.0f;
    //std::uint32_t m_renderMethod = 0x0004;
    //bool m_isPhysicalized = false;

    return true;
}

bool BaseModel::ReadAttributes()
{
    //std::shared_ptr<Mesh> m_modelMesh;
    //std::shared_ptr<Shader> m_modelShader;
    //vec3d m_position = {0.0, 0.0, 0.0};
    //vec3d m_rotation = {0.0, 0.0, 0.0};
    //float m_scale = 1.0f;
    //std::uint32_t m_renderMethod = 0x0004;
    //bool m_isPhysicalized = false;

    return true;
}

bool Shape::WriteAttributes()
{
    return BaseModel::WriteAttributes();
}

bool Shape::ReadAttributes()
{
    return BaseModel::ReadAttributes();
}
bool Terrain::WriteAttributes()
{
    return BaseModel::WriteAttributes();
}

bool Terrain::ReadAttributes()
{
    return BaseModel::ReadAttributes();
}
bool Light::WriteAttributes()
{
    //std::unordered_map<std::shared_ptr<Shader>, std::vector<std::string>> m_shaderUpdateMap;
    //vec4f m_color = {0.4f, 0.9f, 0.8f, 0.9f};

    return true;
}

bool Light::ReadAttributes()
{
    //std::unordered_map<std::shared_ptr<Shader>, std::vector<std::string>> m_shaderUpdateMap;
    //vec4f m_color = {0.4f, 0.9f, 0.8f, 0.9f};

    return true;
}

void Light::Update()
{
    UpdatePosition();
}

void Light::AddMesh(std::shared_ptr<Shader> shader, std::string uniformName)
{
    // TODO: rework map update to be more robust
    if (shader) { m_shaderUpdateMap[shader].push_back(uniformName); }
}

void Light::UpdatePosition()
{
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
        m_position.data[2] -= 1.0;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_position.data[2] += 1.0;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_position.data[0] -= 1.0;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_position.data[0] += 1.0;
    }
}