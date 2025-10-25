// vendors
// project headers
#include "Window.hpp"

#include "../Platform/Windows/WindowsWindow.hpp"
// std library

std::unique_ptr<IWindow> IWindow::Create(const WindowProps& props)
{
    // TODO: Add compiler macros later for different OS
    // Currently always assume Windows
    return std::make_unique<WindowsWindow>(props);
}