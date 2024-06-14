/// project headers
#include "../include/utility.hpp"

// Hash function for mapping specific strings to integers
int hashString(const std::string& str) {
    if (str == "v") return 1;
    if (str == "vt") return 2;
    if (str == "vn") return 3;
    if (str == "f") return 4;
    return 0;
}

// Function to split a string based on a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) { tokens.push_back(token); }

    return tokens;
}

void updateWindowTitle(GLFWwindow* window, float dt, int numActive)
{
    // sprintf(title, "FPS : %-4.0f | Balls : %-10d", 1.0 / dt, numActive);
    std::string title = "FPS: " + std::to_string(static_cast<int>((1.0f/dt)-4.0f)) + 
                        " | Balls: " + std::to_string(numActive);
    glfwSetWindowTitle(window, title.c_str());
}

void displayStats(GLFWwindow* window, int& totalFrames, float& lastFrameTime, int numActive)
{
    float dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
    while (dt < 1.0f / TARGET_FPS) {
        dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
    }
    lastFrameTime = static_cast<float>(glfwGetTime());
    totalFrames++;
    if (totalFrames % 60 == 0) { updateWindowTitle(window, dt, numActive); }
}

void clearErrors()
{
    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }
}