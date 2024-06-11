#pragma once

// std library
#include <iostream>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

// Callback Function Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_enter_callback(GLFWwindow* window, int entered);