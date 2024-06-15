#pragma once

// std library
#include <cmath>
// project headers
#include "fwd_math.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

class Camera
{
public:
    // Camera "eye" location
    vec3f position;
    vec3f resetLoc;
    // Relative target orientation
    vec3f orientation = {0.0, 0.0, -1.0};
    vec3f resetOrient = {0.0, 0.0, -1.0};
    // World view orientation
    vec3f up = {0.0, 1.0, 0.0};
    vec3f right = {1.0, 0.0, 0.0};
    vec3f forward = {0.0, 0.0, -1.0};
    // Protects from moving camera while clicking window into focus
    bool firstClick = true;
    // Screen information
    int width;
    int height;
    // Parameters for modifying camera movement
    float speed = 0.1;
    float sensitivity = 100.0;
    // Various matrices for interacting with shaders
    mat4x4f viewMatrix;
    mat4x4f projectionMatrix;

    Camera( vec3f _pos, int _width, int _height)
        : position{_pos}, width{_width}, height{_height} 
    { 
        viewMatrix.set_all(0.0); 
        projectionMatrix.set_all(0.0);
        resetLoc = _pos;
    }
    
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    
    void updateUniform(unsigned int shaderID, std::string uniform);

    void inputs(GLFWwindow* window);

    void resetCamera(GLFWwindow* window);
};