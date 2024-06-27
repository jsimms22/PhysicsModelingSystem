// project headers
#include "../include/modelClass.hpp"

void Model::destroyMesh() 
{
    this->mesh.VAO.destroy();
}

void Light::input(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->position.data[2] -= 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->position.data[2] += 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->position.data[0] -= 1.0;
    } 
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->position.data[0] += 1.0;
    } 
}

void Light::updateUniform(unsigned int shaderID, std::string uniform)
{
    if (uniform == "lightColor") {
        glUniform4f(glGetUniformLocation(shaderID, "lightColor"), 
                                         this->color.data[0], this->color.data[1], 
                                         this->color.data[2], this->color.data[3]);
    }
    if (uniform == "lightPos") {
        glUniform3f(glGetUniformLocation(shaderID, "lightPos"), 
                                         this->position.data[0], this->position.data[1], 
                                         this->position.data[2]);
    }
}