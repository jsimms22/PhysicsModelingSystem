#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"
// std library
#include <cmath>

class Camera
{
public:
    // Camera "eye" location
    vec3f m_position;
    vec3f m_resetLoc;
    // Relative target orientation
    vec3f m_orientation = {0.0f, 0.0f, -1.0f};
    vec3f m_resetOrient = m_orientation;
    // Camera direction
    vec3f m_direction;
    // World view orientation
    vec3f m_up = {0.0f, 1.0f, 0.0f};
    vec3f m_right = {1.0f, 0.0f, 0.0f};
    vec3f m_forward = {0.0f, 0.0f, -1.0f};
    // Protects from moving camera while clicking window into focus
    bool m_firstClick = true;
    // Screen information
    unsigned int m_width;
    unsigned int m_height;
    // Parameters for modifying camera movement
    float m_speed = 0.1f;
    float m_sensitivity = 100.0f;
    // Various matrices for interacting with shaders
    mat4x4f m_viewMatrix;
    mat4x4f m_projectionMatrix;

    Camera( vec3f _pos, unsigned int _width, unsigned int _height)
        : m_position{_pos}, m_width{_width}, m_height{_height} 
    { 
        m_viewMatrix.set_all(0.0); 
        m_projectionMatrix.set_all(0.0);
        m_resetLoc = _pos;
    }
    
    void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
    
    void UpdateUniform(unsigned int shaderID, std::string uniform);

    void UpdatePosition(GLFWwindow* window);

    void ResetCamera(GLFWwindow* window);
};