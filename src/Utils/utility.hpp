#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
// std library
#include <string>
#include <vector>

// Hash function for mapping specific strings to integers
int HashString(const std::string& str);

// Function to split a string based on a delimiter
std::vector<std::string> SplitString(const std::string& str, char delimiter);
