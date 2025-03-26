// project headers
#include "../include/cameraClass.hpp"

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    vec3_add(this->direction, this->position, this->orientation);
    mat4x4_lookAt(this->viewMatrix, this->position, this->direction, this->up);
    mat4x4_projection(this->projectionMatrix, static_cast<float>(FOVdeg*(M_PI/180.0)), 
                      static_cast<float>(width/height), nearPlane, farPlane);
}

void Camera::UpdateUniform(unsigned int shaderID, std::string uniform)
{
    // Export the view and projection matrix to the shader
    if (uniform == "projection") {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, projectionMatrix.data->data);
    }
    if (uniform == "view") {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, viewMatrix.data->data);
    }
    if (uniform == "camPos") {
        glUniform3f(glGetUniformLocation(shaderID, "camPos"), 
                                         this->position.data[0], this->position.data[1], 
                                         this->position.data[2]);
    }
}

void Camera::UpdatePosition(GLFWwindow* window)
{
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, speed, forward);
        vec3_add(position, position, temp);
    } 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -speed, right);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -speed, forward);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, speed, right);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, speed, up);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -speed, up);
        vec3_add(position, position, temp);
    } 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { 
        speed = 0.8f; 
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f;
    }

    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // Stores the coordinates of the cursor
        double mouseX, mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor 
        // such that they begin in the middle of the screen
        // and then "transforms" them into degrees 
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height; // yaw
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width; // pitch
        // std::cout << rotX << ", " << rotY << std::endl;

        // Calculates upcoming vertical change in the orientation
        vec3f newOrientation = orientation;
        mat3x3_rotate_X(newOrientation, newOrientation, static_cast<float>((M_PI/180.0)*(-rotX)));
        // Decides whether or not the next vertical orientation is legal or not
        if (abs(vec3_angle(newOrientation, up) - static_cast<float>(M_PI/180.0)*(90.0f)) <= static_cast<float>(M_PI/180.0)*(85.0f))
        {
            orientation = newOrientation;
        }
        // Rotates the orientation left and right
        mat3x3_rotate_Y(orientation, orientation, static_cast<float>((M_PI/180.0)*(-rotY)));
        vec3_normal(orientation, orientation);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }
    // std::cout << "orientation: " << position.data[0] << ", "
    //                              << position.data[1] << ", "
    //                              << position.data[2] << std::endl;
}

void Camera::ResetCamera(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        this->position = this->resetLoc;
        this->orientation = this->resetOrient;
    }
}