/// project headers
#include "../include/utility.hpp"



// Hash function for mapping specific strings to integers
int HashString(const std::string& str) {
    if (str == "v") return 1;
    if (str == "vt") return 2;
    if (str == "vn") return 3;
    if (str == "f") return 4;
    return 0;
}

// Function to split a string based on a delimiter
std::vector<std::string> SplitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) { tokens.push_back(token); }

    return tokens;
}
