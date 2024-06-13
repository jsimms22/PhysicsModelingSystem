#pragma once

// std library
#include <cmath>
// project headers
#include "math.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

template <typename UNIT>
class Camera
{
public:
    vec3<UNIT> position;
    vec3<UNIT> orientation = {0.0, 0.0, -1.0};
    vec3<UNIT> up = {0.0, 1.0, 0.0};

    bool firstClick = true;

    int height;
    int width;

    UNIT speed = 0.0;
    UNIT sensitivity = 100.0;

    Camera(int _width, int _height, vec3<UNIT> _pos)
        : width{_width}, height{_height}, position{_pos} { }
    
    void viewMatrix(UNIT FOVdeg, UNIT nearPlane, UNIT farPlane, unsigned int shaderID)
    {
        // updateVectors(camera);
        mat4x4<UNIT> view, projection;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) 
                view.data[i].data[j] = 0.0;
        mat4x4_copy(projection, view);
        vec3<UNIT> temp;
        // std::cout << "Position: ";
        // std::cout << position.data[0] << ", " << position.data[1] << ", " << position.data[2] << std::endl;
        vec3_add(temp, this->position, this->orientation);
        //position = camera eye, temp = center, 
        mat4x4_lookAt(view, this->position, temp, this->up);
        mat4x4_projection(projection, static_cast<UNIT>(FOVdeg*(M_PI/180.0)), static_cast<UNIT>(width/height), nearPlane, farPlane);

        // Export the view and projection matrix to the shader
	    glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, view.data->data);
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, projection.data->data);
    }

    void inputs(GLFWwindow* window)
    {
        // Handles key inputs
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            vec3<UNIT> temp;
            vec3_scale(temp, speed, orientation);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            // position += speed * -glm::normalize(glm::cross(orientation, up));
            vec3<UNIT> temp;
            vec3_cross(temp, orientation, up);
            vec3_normal(temp, temp);
            vec3_scale(temp, -speed, temp);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            // position += speed * -orientation;
            vec3<UNIT> temp;
            vec3_scale(temp, -speed, orientation);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            // position += speed * glm::normalize(glm::cross(orientation, up));
            vec3<UNIT> temp;
            vec3_cross(temp, orientation, up);
            vec3_normal(temp, temp);
            vec3_scale(temp, speed, temp);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            // position += speed * up;
            vec3<UNIT> temp;
            vec3_scale(temp, speed, up);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            // position += speed * -up;
            vec3<UNIT> temp;
            vec3_scale(temp, -speed, up);
            vec3_add(position, position, temp);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }

        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwSetCursorPos(window, (width / 2), (height / 2));
                firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees 
            float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
            float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

            // Calculates upcoming vertical change in the orientation
            // glm::vec3 neworientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

            // Decides whether or not the next vertical orientation is legal or not
            // if (abs(glm::angle(neworientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            // {
            //     orientation = neworientation;
            // }

            // Rotates the orientation left and right
            // orientation = glm::rotate(orientation, glm::radians(-rotY), up);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            firstClick = true;
        }
    }
};