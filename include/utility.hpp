#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

constexpr unsigned int TARGET_FPS {144};

// Hash function for mapping specific strings to integers
int HashString(const std::string& str);

// Function to split a string based on a delimiter
std::vector<std::string> SplitString(const std::string& str, char delimiter);

// Update title bar
void UpdateWindowTitle(GLFWwindow* window, float dt, int numActive);

// Calculate average FPS
void DisplayStats(GLFWwindow* window, int& totalFrames, float& lastFrameTime, int numActive);

// Clear openGL error buffer
void ClearErrors();