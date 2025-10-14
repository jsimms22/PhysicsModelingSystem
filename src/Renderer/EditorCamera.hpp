#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../Renderer/Camera.hpp"
// std library
#include <cmath>

class EditorCamera : public Camera
{
public:
    EditorCamera() = default;
    EditorCamera(const mat4x4d& matrix)
        : Camera(matrix) {}
    EditorCamera(const vec3d& _pos, const float _width, const float _height, const mat4x4d& matrix = {})
        : Camera(matrix), m_position{_pos}, m_resetLoc{_pos}, m_width{_width}, m_height{_height} {}
    
    void OnUpdate() override;
    void OnEvent(Event& e) override {};

    void UpdateViewport(float width, float height);

    const vec3d GetPosition() const { return m_position; }

    const vec3d GetDirection() const { return m_forward; }

private:
    void UpdatePosition();
    void ResetCamera();
    void UpdateProjection();
    void UpdateView();
    void UpdateMatrix();

    // EditorCamera "eye" location
    vec3d m_position = {0.0f, 0.0f, 0.0f};
    vec3d m_resetLoc = m_position;
    // World view orientation
    const vec3d m_up = {0.0f, 1.0f, 0.0f};
    const vec3d m_right = {1.0f, 0.0f, 0.0f};
    const vec3d m_forward = {0.0f, 0.0f, -1.0f};
    // Relative target orientation
    vec3d m_orientation = {0.0f, 0.0f, -1.0f};
    vec3d m_resetOrient = m_orientation;
    // EditorCamera direction
    vec3d m_direction;
    // Protects from moving camera while clicking window into focus
    bool m_firstClick = true;
    // Screen information
    float m_width = 1200.f;
    float m_height = 1200.f;
    double m_aspectRatio = static_cast<double>(m_width / m_height);
    // Parameters for modifying camera movement
    double m_speed = 0.1;
    double m_sensitivity = 100.0;
    // Various matrices for interacting with shaders
    mat4x4d m_viewMatrix;
    mat4x4d m_projectionMatrix;
    // Information needed to input to the camera view and projection matrices
    float m_FOV = 25.0f;
    double m_nearPlane = 0.1;
    double m_farPlane = 10000.0;
};