// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"

#include "../types.hpp"

#include "../Core/Application.hpp"
//#include "../Core/Mouse.hpp"
#include "../Core/Input.hpp"

#include "../Physics/force.hpp"

#include "../Renderer/Graphics.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/EditorCamera.hpp"
#include "../Renderer/Renderer.hpp"

#include "../Scene/Model.hpp"

#include "../Events/EventNotifier.hpp"
// std library
#include <vector>
#include <cmath>
#include <string>
#include <functional>
#include <utility>

// Define the static member variable outside the class
std::weak_ptr<Application> Application::s_applicationInstance;

Application::Application(Private p)
{
    m_spWindow = IWindow::Create();
    m_spWindow->SetEventCallback([this](Event& e) -> void { this->OnEvent(e); });

    Renderer::Init();
}

void Application::OnEvent(Event& e)
{
    std::cout << e << std::endl;
    EventNotifier notifier(e);
    notifier.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) -> bool { return this->OnWindowClose(e); });
    notifier.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) -> bool { return this->OnWindowResize(e); });
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
    std::cout << "Window resizing\n";
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_bMinimized = true;
        return false;
    }

    m_bMinimized = false;
    
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    std::cout << "Window closing\n";
    m_bRunning = false;
    return true;
}

std::shared_ptr<Application> Application::Create()
{
    if (auto instance = s_applicationInstance.lock()) {
        return instance;
    } else {
        instance = std::make_shared<Application>(Application::Private());
        s_applicationInstance = instance;
        return instance;
    }
}

void Application::Run()
{
    // Shaders
    std::shared_ptr<Shader> multiLights = std::make_shared<Shader>("shaders/multiple_vertex.glsl", "shaders/multiple_fragment.glsl");
    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
        
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj");
    //std::shared_ptr<Mesh> carMesh = std::make_shared<Mesh>("models/sportsCar.obj");
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj");
    
    std::vector<std::shared_ptr<IModel>> models;
    std::vector<std::shared_ptr<IModel>> lights;
    // Init floor terrain
    models.push_back(CreateModelFactory(ModelType::Terrain, 
                                        std::make_shared<Mesh>(FloorVertex(100, 10, 10), FloorIndex(100)), 
                                        multiLights, 
                                        {0.0f, -12.f, 0.0f}, 
                                        100.0f,
                                        GL_LINES,
                                        false));
    // Init container
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                        cubeMesh, 
                                        multiLights, 
                                        {0.0f, 0.0f, 0.0f}, 
                                        12.f));
    // Init sphere
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                        sphereMesh,
                                        multiLights,
                                        {25.0f, 0.0f, 25.0f},
                                        5.f));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + rand()%30, 5.0f, 5 + rand()%30}, 
                                        1.f,
                                        {.1f,.5f,.9f,.8f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + -rand()%30, 25.0f, 5 + rand()%30}, 
                                        1.f,
                                        {.2f,.6f,1.0f,.7f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + -rand()%30, -5.0f, 5 + -rand()%30}, 
                                        1.f,
                                        {.3f,.7f,.9f,.6f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + rand()%30, 12.0f, 5 + -rand()%30}, 
                                        1.f,
                                        {.4f,.8f,.7f,.5f}));

    EditorCamera camera = EditorCamera(vec3f({0.0f, 0.0f, 125.0f}), m_spWindow->GetWidth(), m_spWindow->GetHeight());
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();

    m_stats.lastFrameTime = static_cast<float>(glfwGetTime());
    float theta = 0.0f;
    while (m_bRunning) 
    {
        /* Clears back buffer before new buffer is drawn */
        Renderer::Clear();

        if (Input::IsKeyPressed(KeyCode::Escape)) { Application::Close(); }
        camera.UpdateViewport(m_spWindow->GetWidth(),m_spWindow->GetHeight());
        camera.OnUpdate();

        /* Shader Uniforms */
        // Multiple Lights Shader Lighting
        // directional light:
        multiLights->SetUniform4fm("cameraMatrix", camera.GetCameraMatrix());
        multiLights->SetUniform3fv("cameraPosition", camera.GetPosition());
        multiLights->SetUniform3fv("dirLight.position", {0.0f, -10.0f, 0.0f});
        multiLights->SetUniform3fv("dirLight.ambient", {0.05f, 0.05f, 0.05f});
        multiLights->SetUniform3fv("dirLight.diffuse", {0.4f, 0.4f, 0.4f});
        multiLights->SetUniform3fv("dirLight.specular", {0.5f, 0.5f, 0.5f});
        // spotlight
        std::size_t lightIndex {};
        for (std::shared_ptr<IModel> light : lights) 
        {
            switch (lightIndex)
            {
                case 0:
                {
                    light->SetPosition({-30.f*cos(theta * (M_PI/180.f)), light->GetPosition()[1], 30.f*sin(theta * (M_PI/180.f))});
                    break;
                }
                case 1:
                {
                    light->SetPosition({-30.f*cos(theta * (M_PI/180.f)), -30.f*sin(theta * (M_PI/180.f)), light->GetPosition()[1]});
                    break;
                }
                case 2:
                {
                    light->SetPosition({30.f*cos(theta * (M_PI/180.f)), light->GetPosition()[1], -30.f*sin(theta * (M_PI/180.f))});
                    break;
                }
                case 3:
                {
                    light->SetPosition({-30.f*cos(theta * (M_PI/180.f)), light->GetPosition()[1], -30.f*sin(theta * (M_PI/180.f))});
                    break;
                }
            }
            multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].position", light->GetPosition());
            multiLights->SetUniform4fv("pointLights[" + std::to_string(lightIndex) + "].color", light->GetColor());
            multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].ambient", {0.05f, 0.05f, 0.05f});
            multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].diffuse", {0.8f, 0.8f, 0.8f});
            multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].specular", {1.0f, 1.0f, 1.0f});
            multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].constant", 1.0f);
            multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].linear", 0.04f);
            multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].quadratic", 0.0075f);
            ++lightIndex;
        }
         
        // Light Shader Lighting - all lights are the same so use the last one
        lightShader->SetUniform4fm("cameraMatrix", camera.GetCameraMatrix());
        for (std::shared_ptr<IModel> light : lights) 
        {
            lightShader->SetUniform4fv("lightColor", light->GetColor());
            renderer->DrawModelMesh(light); 
        }
        for (std::shared_ptr<IModel> model : models) 
        { 
            renderer->DrawModelMesh(model); 
        }
                 
        /* Clean Up and Measure */
        m_spWindow->OnUpdate();
        ClearErrors();
        DisplayStats();

        if (theta < 360 || theta >= 0) { 
            theta = theta + (60 * m_stats.deltaTime); 
        }
        else { 
            theta = theta - (60 * m_stats.deltaTime); 
        }
    }
}

void Application::DisplayStats() 
{
    m_stats.deltaTime = static_cast<float>(glfwGetTime()) - m_stats.lastFrameTime;
    while (m_stats.deltaTime < (1.0f / m_stats.targetFPS)) {
        m_stats.deltaTime = static_cast<float>(glfwGetTime()) - m_stats.lastFrameTime;
    }
    m_stats.lastFrameTime = static_cast<float>(glfwGetTime());
    m_stats.totalFrames++;
    if (m_stats.totalFrames % m_stats.targetFPS == 0) { m_spWindow->UpdateWindowTitle(m_stats.deltaTime, m_stats.totalModels); }
}

void Application::ClearErrors() const
{
    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }
}