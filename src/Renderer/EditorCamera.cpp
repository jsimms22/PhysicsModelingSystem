// vendors
// project headers
#include "../Renderer/EditorCamera.hpp"
#include "../Core/Input.hpp"
// std library

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
    mat4x4_mul(m_cameraMatrix, m_projectionMatrix, m_viewMatrix);
}

void EditorCamera::UpdateProjection()
{
    m_aspectRatio = m_width / m_height;
    mat4x4_projection(m_projectionMatrix, static_cast<double>(m_FOV)*(M_PI / 180.0), 
                      m_aspectRatio, m_nearPlane, m_farPlane);
}

void EditorCamera::UpdateView()
{
    vec3_add(m_direction, m_position, m_orientation);
    mat4x4_lookAt(m_viewMatrix, m_position, m_direction, m_up);
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
    if (Input::IsKeyPressed(KeyCode::W)) {
        vec3d temp;
        vec3_scale(temp, m_speed, m_forward);
        vec3_add(m_position, m_position, temp);
    }
    if (Input::IsKeyPressed(KeyCode::A)) {
        vec3d temp;
        vec3_scale(temp, -m_speed, m_right);
        vec3_add(m_position, m_position, temp);
    }
    if (Input::IsKeyPressed(KeyCode::S)) {
        vec3d temp;
        vec3_scale(temp, -m_speed, m_forward);
        vec3_add(m_position, m_position, temp);
    }
    
    if (Input::IsKeyPressed(KeyCode::D)) {
        vec3d temp;
        vec3_scale(temp, m_speed, m_right);
        vec3_add(m_position, m_position, temp);
    }
    
    if (Input::IsKeyPressed(KeyCode::Space)) {
        vec3d temp;
        vec3_scale(temp, m_speed, m_up);
        vec3_add(m_position, m_position, temp);
    }
    
    if (Input::IsKeyPressed(KeyCode::LeftControl)) {
        vec3d temp;
        vec3_scale(temp, -m_speed, m_up);
        vec3_add(m_position, m_position, temp);
    }
    if (Input::IsKeyPressed(KeyCode::LeftShift)) {
        m_speed = 2.0;
    } else if (Input::IsKeyReleased(KeyCode::LeftShift)) {
        m_speed = 1.0;
    }

    // Handles mouse inputs
    if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft)) {
        Input::ShowMouseCursor(false);

        // Prevents camera from jumping on the first click
        if (m_firstClick) {
            Input::SetMousePositionCenter();
            m_firstClick = false;
        }

        vec2f mousePosition = Input::GetMousePosition();

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees 
        double rotX = m_sensitivity * static_cast<double>((mousePosition[1] - (m_height / 2)) / m_height); // yaw
        double rotY = m_sensitivity * static_cast<double>((mousePosition[0] - (m_width / 2)) / m_width); // pitch

        // Calculates upcoming vertical change in the orientation
        vec3d newOrientation = m_orientation;
        mat3x3_rotate_X(newOrientation, newOrientation, (M_PI/180.0)*(-rotX));

        // Decides whether or not the next vertical orientation is legal or not
        if (abs(vec3_angle(newOrientation, m_up) - (M_PI/180.0)*90.0) <= (M_PI/180.0)*85.0)
        {
            m_orientation = newOrientation;
        }

        // Rotates the orientation left and right
        mat3x3_rotate_Y(m_orientation, m_orientation, (M_PI/180.0)*(-rotY));
        vec3_normal(m_orientation, m_orientation);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        Input::SetMousePositionCenter();
    } 
    else if (Input::IsMouseButtonReleased(MouseCode::ButtonLeft)) {
        Input::ShowMouseCursor(true);
        m_firstClick = true;
    }
}

void EditorCamera::ResetCamera()
{
    if (Input::IsKeyPressed(KeyCode::F1)) {
        m_position = m_resetLoc;
        m_orientation = m_resetOrient;
    }
}