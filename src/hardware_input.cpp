// project headers
#include "../include/hardware_input.hpp"

void ProcessInput(GLFWwindow* window)
{
    //std::cout << "input test" << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}