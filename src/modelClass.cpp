// project headers
#include "../include/modelClass.hpp"

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