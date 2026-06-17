#pragma once

// vendors
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
// project headers
#include "Camera.hpp"
// std library

class EditorCamera : public Camera
{
public:
    EditorCamera() = default;
    EditorCamera(const glm::dmat4x4& matrix)
        : Camera(matrix) {}
    EditorCamera(const glm::dvec3& _pos, const float _width, const float _height, const glm::dmat4x4& matrix = {})
        : Camera(matrix), m_position{_pos}, m_resetLoc{_pos}, m_width{_width}, m_height{_height} {}
    
    void OnUpdate() override;
    void OnEvent(Event& /*e*/) override {};

    void UpdateViewport(float width, float height);

    const glm::dvec3 GetPosition() const { return m_position; }

    const glm::dvec3 GetDirection() const { return m_forward; }

private:
    void UpdatePosition();
    void ResetCamera();
    void UpdateProjection();
    void UpdateView();
    void UpdateMatrix();

    // EditorCamera "eye" location
    glm::dvec3 m_position{0.};
    glm::dvec3 m_resetLoc = m_position;
    // World view orientation
    const glm::dvec3 m_up = {0., 1., 0.};
    const glm::dvec3 m_right = {1., 0., 0.};
    const glm::dvec3 m_forward = {0., 0., -1.};
    // Relative target orientation
    glm::dvec3 m_orientation = {0., 0., -1.};
    glm::dvec3 m_resetOrient = m_orientation;
    // EditorCamera direction
    glm::dvec3 m_direction;
    // Protects from moving camera while clicking window into focus
    bool m_firstClick = true;
    // Screen information
    float m_width = 1200.f;
    float m_height = 1200.f;
    double m_aspectRatio = static_cast<double>(m_width / m_height);
    // Parameters for modifying camera movement
    double m_speed = 0.1;
    double m_sensitivity = 100.;
    // Various matrices for interacting with shaders
    glm::mat4x4 m_viewMatrix;
    glm::mat4x4 m_projectionMatrix;
    // Information needed to input to the camera view and projection matrices
    float m_FOV = 25.0f;
    double m_nearPlane = 0.1;
    double m_farPlane = 10000.;
};