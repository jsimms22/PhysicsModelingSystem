#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Hash function for mapping specific strings to integers
int hashString(const std::string& str);

// Function to split a string based on a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter);
