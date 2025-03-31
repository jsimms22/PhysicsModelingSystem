// vendors
// project headers
#include "../Core/Application.hpp"
#include "../Renderer/EditorCamera.hpp"
// std library

void EditorCamera::Update()
{
    auto app = Application::GetApplication();
    if (app) {
        ResetCamera(app->GetGLFWwindow()); // checks if user wants to reset camera to initial position
        UpdatePosition(app->GetGLFWwindow());  // use wasd + shift + ctrl
    }
    UpdateMatrix();
}

void EditorCamera::UpdateMatrix()
{
    vec3_add(m_direction, m_position, m_orientation);
    mat4x4_lookAt(m_viewMatrix, m_position, m_direction, m_up);
    mat4x4_projection(m_projectionMatrix, static_cast<float>(m_FOV*(M_PI / 180.0f)), 
                      static_cast<float>(m_width / m_height), m_nearPlane, m_farPlane);
    
    mat4x4_mul(m_cameraMatrix, m_projectionMatrix, m_viewMatrix);
}

void EditorCamera::UpdatePosition(GLFWwindow* window)
{
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, m_speed, m_forward);
        vec3_add(m_position, m_position, temp);
    } 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -m_speed, m_right);
        vec3_add(m_position, m_position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -m_speed, m_forward);
        vec3_add(m_position, m_position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, m_speed, m_right);
        vec3_add(m_position, m_position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, m_speed, m_up);
        vec3_add(m_position, m_position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -m_speed, m_up);
        vec3_add(m_position, m_position, temp);
    } 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { 
        m_speed = 2.0f; 
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        m_speed = 1.0f;
    }

    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (m_firstClick) {
            glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
            m_firstClick = false;
        }

        // Stores the coordinates of the cursor
        double mouseX, mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor 
        // such that they begin in the middle of the screen
        // and then "transforms" them into degrees 
        float rotX = m_sensitivity * static_cast<float>((mouseY - static_cast<float>((m_height / 2))) / m_height); // yaw
        float rotY = m_sensitivity * static_cast<float>((mouseX - (m_width / 2)) / m_width); // pitch
        // std::cout << rotX << ", " << rotY << std::endl;

        // Calculates upcoming vertical change in the orientation
        vec3f newOrientation = m_orientation;
        mat3x3_rotate_X(newOrientation, newOrientation, static_cast<float>((M_PI/180.0)*(-rotX)));
        // Decides whether or not the next vertical orientation is legal or not
        if (abs(vec3_angle(newOrientation, m_up) - static_cast<float>(M_PI/180.0)*(90.0f)) <= static_cast<float>(M_PI/180.0)*(85.0f))
        {
            m_orientation = newOrientation;
        }
        // Rotates the orientation left and right
        mat3x3_rotate_Y(m_orientation, m_orientation, static_cast<float>((M_PI/180.0)*(-rotY)));
        vec3_normal(m_orientation, m_orientation);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        m_firstClick = true;
    }
    // std::cout << "orientation: " << position.data[0] << ", "
    //                              << position.data[1] << ", "
    //                              << position.data[2] << std::endl;
}

void EditorCamera::ResetCamera(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        m_position = m_resetLoc;
        m_orientation = m_resetOrient;
    }
}