// vendors
// project headers
#include "Window.hpp"
#include "WindowAPI.hpp"

#include "../Platform/GLFWContext/GLFWWindow.hpp"
//#include "../Platform/QTContext/QT6Window.hpp"
// std library

std::unique_ptr<IWindow> IWindow::Create(const WindowProps& props)
{
    switch (WindowAPI::GetAPI())
    {
        case WindowAPI::API::GLFW: return std::make_unique<GLFWWindow>(props);
        //case WindowAPI::API::QT6: return std::make_unique<QT6Window>(props);
        case WindowAPI::API::None:
        default: return nullptr;
    }
    
}