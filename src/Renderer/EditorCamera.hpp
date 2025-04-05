#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../Renderer/Camera.hpp"
// std library
#include <cmath>

class EditorCamera : public Camera
{
public:
    EditorCamera() = default;
    EditorCamera(const mat4x4f& matrix)
        : Camera(matrix) {}
    EditorCamera(const vec3f& _pos, const float _width, const float _height, const mat4x4f& matrix = {})
        : Camera(matrix), m_position{_pos}, m_resetLoc{_pos}, m_width{_width}, m_height{_height} {}
    
    void OnUpdate() override;
    void OnEvent(Event& e) override {};

    void UpdateViewport(float width, float height);

    const vec3f& GetPosition() const { return m_position; }

private: // methods
    void UpdatePosition();
    void ResetCamera();

    void UpdateProjection();
    void UpdateView();
    void UpdateMatrix();

private: // members
    // EditorCamera "eye" location
    vec3f m_position = {0.0f, 0.0f, 0.0f};
    vec3f m_resetLoc = m_position;
    // World view orientation
    const vec3f m_up = {0.0f, 1.0f, 0.0f};
    const vec3f m_right = {1.0f, 0.0f, 0.0f};
    const vec3f m_forward = {0.0f, 0.0f, -1.0f};
    // Relative target orientation
    vec3f m_orientation = {0.0f, 0.0f, -1.0f};
    vec3f m_resetOrient = m_orientation;
    // EditorCamera direction
    vec3f m_direction;
    // Protects from moving camera while clicking window into focus
    bool m_firstClick = true;
    // Screen information
    float m_width = 1200.f;
    float m_height = 1200.f;
    float m_aspectRatio = m_width / m_height;
    // Parameters for modifying camera movement
    float m_speed = 0.1f;
    float m_sensitivity = 100.0f;
    // Various matrices for interacting with shaders
    mat4x4f m_viewMatrix;
    mat4x4f m_projectionMatrix;
    // Information needed to input to the camera view and projection matrices
    float m_FOV = 25.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
};