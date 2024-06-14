// project headers
#include "../include/camera.hpp"

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    vec3f temp;
    vec3_add(temp, this->position, this->orientation);
    //position = camera eye, temp = center, 
    mat4x4_lookAt(this->viewMatrix, this->position, temp, this->up);
    mat4x4_projection(this->projectionMatrix, static_cast<float>(FOVdeg*(M_PI/180.0)), 
                      static_cast<float>(width/height), nearPlane, farPlane);
}

void Camera::updateUniform(unsigned int shaderID, std::string uniform)
{
    // Export the view and projection matrix to the shader
    if (uniform == "projection") {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, projectionMatrix.data->data);
    }
    if (uniform == "view") {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, viewMatrix.data->data);
    }
}

void Camera::inputs(GLFWwindow* window)
{
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        vec3f temp1;
        vec3_scale(temp1, speed, orientation);
        vec3_add(position, position, temp1);
    } 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3f temp;
        vec3_cross(temp, orientation, up);
        vec3_normal(temp, temp);
        vec3_scale(temp, -speed, temp);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        vec3f temp;
        vec3_scale(temp, -speed, orientation);
        vec3_add(position, position, temp);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3f temp;
        vec3_cross(temp, orientation, up);
        vec3_normal(temp, temp);
        vec3_scale(temp, speed, temp);
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
        speed = 0.4f; 
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

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees 
        // float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Calculates upcoming vertical change in the orientation
        // glm::vec3 neworientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        // Decides whether or not the next vertical orientation is legal or not
        // if (abs(glm::angle(neworientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        // {
        //     orientation = neworientation;
        // }

        // Rotates the orientation left and right
        mat3x3_rotate_Y(orientation, orientation, static_cast<float>((M_PI/180.0)*(-rotY)));

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }   
}

void Camera::resetCamera(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        this->position = this->resetLoc;
        this->orientation = this->resetOrient;
    }
}