// vendors
// project headers
#include "../Core/Window.hpp"
#include "../Core/globalSettings.hpp"    // Contains our settings singleton
#include "../Core/Application.hpp"
// std library
#include <string>
#include <stdexcept>

bool WindowContext::Initialize()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "GLFW init failure" << std::endl;
        return m_bInitialized;
    }

    // Tells GLFW what version of opengl we are using: 3.3.0 NVIDIA 552.44
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we only want the modern functions via core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_bInitialized = true;
    return m_bInitialized;
}

Window::Window(WindowProps props)
    : m_windowProps{props}
{
    m_pContext = std::make_unique<WindowContext>();
    if (!m_pContext->Initialize()) {
        throw std::runtime_error("Failed to initialize GLFW context.");
    }

    // Create window
    m_pWindow = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.title, NULL, NULL);
    if (!m_pWindow) {
        std::cout << "Window creation failure" << std::endl;
        throw std::runtime_error("Failed to create GLFW window.");
    }

    // Make context current
    glfwMakeContextCurrent(m_pWindow);

    // Initialize GLEW (or any other OpenGL function loader)
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failure" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW.");
    }

    // OpenGL settings
    glViewport(0, 0, m_windowProps.width, m_windowProps.height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3.0f);
    // Vsync
    glfwSwapInterval(1);
}

Window::~Window() { if (m_pWindow) { glfwDestroyWindow(m_pWindow); } }

void Window::SwapBuffers() { glfwSwapBuffers(m_pWindow); }

void Window::PollEvents() { glfwPollEvents(); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_pWindow); }

void Window::ProcessInput(Mouse& mouse)
{
    // Display all active errors and clear buffer
    ClearErrors();

    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) { 
        glfwSetWindowShouldClose(m_pWindow, true);
    }
    
    mouse.UpdateMouse(m_pWindow, mouse.GetX(), mouse.GetY());
}

void Window::ClearErrors() const
{
    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }
}

void Window::DisplayStats()
{
    GlobalSettings& settings = GlobalSettings::Instance();
    auto app = Application::GetApplication();
    if (!app) { return; }

    app->m_deltaTime = static_cast<float>(glfwGetTime()) - app->m_fLastFrameTime;
    while (app->m_deltaTime < 1.0f / settings.TARGET_FPS) {
        app->m_deltaTime = static_cast<float>(glfwGetTime()) - app->m_fLastFrameTime;
    }
    app->m_fLastFrameTime = static_cast<float>(glfwGetTime());
    app->m_totalFrames++;
    if (app->m_totalFrames % settings.TARGET_FPS == 0) { UpdateWindowTitle(app->m_deltaTime, app->m_totalModels); }
}

void Window::UpdateWindowTitle(float dt, int numActive)
{
    // sprintf(title, "FPS : %-4.0f | Balls : %-10d", 1.0 / dt, numActive);
    std::string title = "FPS: " + std::to_string(static_cast<int>((1.0f/dt)-4.0f)) + 
                        " | Balls: " + std::to_string(numActive);
    glfwSetWindowTitle(m_pWindow, title.c_str());
}