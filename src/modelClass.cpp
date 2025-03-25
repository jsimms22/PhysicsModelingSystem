// project headers
#include "../include/modelClass.hpp"

Model::Model(std::shared_ptr<Mesh> _sourceMesh,
             float _scalar, 
             unsigned int _renderMethod)
: m_modelMesh{_sourceMesh}, m_scale{_scalar}, m_renderMethod{_renderMethod} 
{ 
}

void Model::DestroyMesh() 
{
    m_modelMesh->VAO.Destroy();
}

Light::Light(std::shared_ptr<Mesh> _sourceMesh,
             float _scalar, 
             unsigned int _renderMethod)
: Model{_sourceMesh, _scalar, _renderMethod} 
{
}

void Light::UpdatePosition(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_position.data[2] -= 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_position.data[2] += 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_position.data[0] -= 1.0;
    } 

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_position.data[0] += 1.0;
    } 
}

void Light::UpdateUniform(const unsigned int& shaderID, const std::string& uniform) 
{
    if (uniform == "lightColor") {
        glUniform4f(glGetUniformLocation(shaderID, "lightColor"),
                    m_color.data[0], 
                    m_color.data[1], 
                    m_color.data[2], 
                    m_color.data[3]);
    }
    
    if (uniform == "lightPos") {
        glUniform3f(glGetUniformLocation(shaderID, "lightPos"), 
                    m_position.data[0], 
                    m_position.data[1], 
                    m_position.data[2]);
    }
}