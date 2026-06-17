// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// project headers
#include "EditorCamera.hpp"

#include "../Core/Input.hpp"
#include "../fwd_math.hpp"
// std library
#include <cmath>

void EditorCamera::OnUpdate()
{
    ResetCamera(); // checks if user wants to reset camera to initial position
    UpdatePosition();  // use wasd + shift + ctrl
    UpdateMatrix();
}

void EditorCamera::UpdateMatrix()
{
    UpdateView();
    UpdateProjection();
    m_cameraMatrix = m_projectionMatrix * m_viewMatrix;
}

void EditorCamera::UpdateProjection()
{
    m_aspectRatio = m_width / m_height;
    m_projectionMatrix = glm::perspective(static_cast<double>(glm::radians(m_FOV)),
        m_aspectRatio,
        m_nearPlane,
        m_farPlane);
}

void EditorCamera::UpdateView()
{
    m_direction = m_position + m_orientation;
    m_viewMatrix = glm::lookAt(m_position, m_direction, m_up);
}

void EditorCamera::UpdateViewport(float width, float height)
{
    m_width = width;
    m_height = height;
    m_aspectRatio = static_cast<double>(m_width / m_height);
}

void EditorCamera::UpdatePosition()
{
    // Handles key inputs
    if (Input::IsKeyPressed(KeyCode::W))
    {
        m_position += m_speed * m_orientation;
    }

    if (Input::IsKeyPressed(KeyCode::A))
    {
        m_position += -m_speed * glm::normalize(glm::cross(m_orientation, m_up));
    }

    if (Input::IsKeyPressed(KeyCode::S))
    {
        m_position += -m_speed * m_orientation;
    }

    if (Input::IsKeyPressed(KeyCode::D))
    {
        m_position += m_speed * glm::normalize(glm::cross(m_orientation, m_up));
    }

    if (Input::IsKeyPressed(KeyCode::Space))
    {
        m_position += m_speed * m_up;
    }

    if (Input::IsKeyPressed(KeyCode::LeftControl))
    {
        m_position += -m_speed * m_up;
    }

    if (Input::IsKeyPressed(KeyCode::LeftShift))
    {
        m_speed = 3.;
    }
    else if (Input::IsKeyReleased(KeyCode::LeftShift))
    {
        m_speed = 1.;
    }

    // Handles mouse inputs
    if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft))
    {
        Input::ShowMouseCursor(false);

        // Prevents camera from jumping on the first click
        if (m_firstClick)
        {
            Input::SetMousePositionCenter();
            m_firstClick = false;
        }

        const auto mousePosition = Input::GetMousePosition();

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees
        const double rotX = m_sensitivity * static_cast<double>((mousePosition.y - (m_height / 2)) / m_height); // yaw
        const double rotY = m_sensitivity * static_cast<double>((mousePosition.x - (m_width / 2)) / m_width); // pitch
        const glm::dvec3 newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_orientation, m_up)));

        // angle check...
        if (std::abs(glm::angle(newOrientation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            m_orientation = newOrientation;
        }

        m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), m_up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        Input::SetMousePositionCenter();
    }
    else if (Input::IsMouseButtonReleased(MouseCode::ButtonLeft))
    {
        Input::ShowMouseCursor(true);
        m_firstClick = true;
    }
}

void EditorCamera::ResetCamera()
{
    if (Input::IsKeyPressed(KeyCode::F1))
    {
        m_position = m_resetLoc;
        m_orientation = m_resetOrient;
    }
}