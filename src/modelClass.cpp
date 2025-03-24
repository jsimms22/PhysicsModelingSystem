// project headers
#include "../include/modelClass.hpp"

Model::Model(std::shared_ptr<Mesh> _sourceMesh,
             float _scalar, 
             unsigned int _renderMethod, 
             vec3f _positionVec /*= {0.0f, 0.0f, 0.0f}*/, 
             vec3f _rotationVec /*= {0.0f, 0.0f, 0.0f}*/)
: m_modelMesh{_sourceMesh}, m_scale{_scalar}, m_renderMethod{_renderMethod} 
{ 
    m_position = _positionVec;
    m_rotation = _rotationVec;
}

void Model::DestroyMesh() 
{
    //this->mesh.VAO.destroy();
}

Light::Light(std::shared_ptr<Mesh> _sourceMesh,
             float _scalar, 
             unsigned int _renderMethod,
             vec4f _color /*= {255.0f, 255.0f, 255.0f}*/,
             vec3f _positionVec /*= {0.0f, 0.0f, 0.0f}*/, 
             vec3f _rotationVec /*= {0.0f, 0.0f, 0.0f}*/)
: Model{_sourceMesh, _scalar, _renderMethod} 
{
    m_color = _color;
    m_position = _positionVec;
    m_rotation = _rotationVec;
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