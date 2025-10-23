// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "WindowsWindow.hpp"

#include "../../Core/Application.hpp"
#include "../../Core/Input.hpp"
// std library

bool Input::IsKeyPressed(const KeyCode keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
    return state == GLFW_PRESS;
}

bool Input::IsKeyReleased(const KeyCode keycode)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
    return state == GLFW_RELEASE;
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

bool Input::IsMouseButtonReleased(const MouseCode button)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_RELEASE;
}

void Input::ShowMouseCursor(const bool show)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    if (!show) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
    else { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
}

vec2f Input::GetMousePosition()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return { static_cast<float>(xpos), static_cast<float>(ypos) };
}

void Input::SetMousePosition(const vec2f position)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    glfwSetCursorPos(window, (position[0]), (position[1]));
}

void Input::SetMousePositionCenter()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow().GetPlatformWindow());
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, (width / 2), (height / 2));
}

float Input::GetMouseX()
{
    return GetMousePosition()[0];
}

float Input::GetMouseY()
{
    return GetMousePosition()[1];
}