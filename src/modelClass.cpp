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