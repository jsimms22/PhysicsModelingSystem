// vendors
// project headers
#include "../Core/Window.hpp"
#include "../Platform/Windows/WindowsWindow.hpp"
// std library

std::shared_ptr<IWindow> IWindow::Create(const WindowProps& props)
{
    return std::make_shared<WindowsWindow>(props);
}