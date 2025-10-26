// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project headers
#include "../Scene/Model.hpp"
// std library

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