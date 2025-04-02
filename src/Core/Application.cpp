// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"

#include "../types.hpp"

#include "../Core/Application.hpp"
#include "../Core/globalSettings.hpp"    // Contains our settings singleton 
#include "../Core/Mouse.hpp"
#include "../Core/sys_callbacks.hpp"

#include "../Physics/force.hpp"

#include "../Renderer/Graphics.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/EditorCamera.hpp"
#include "../Renderer/Renderer.hpp"

#include "../Scene/Model.hpp"

#include "../Events/WindowEvents.hpp"
#include "../Events/ApplicationEvents.hpp"
// std library
#include <vector>
#include <cmath>
#include <string>

// Define the static member variable outside the class
std::weak_ptr<Application> Application::s_instance;

Application::Application(Private p)
{
    m_pWindow = IWindow::Create();
    WindowResizeEvent e(1400,1400);
}

void Application::Run()
{
    GlobalSettings& settings = GlobalSettings::Instance();

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
                                        {0.0f, -(settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f), 0.0f}, 
                                        100.0f,
                                        GL_LINES,
                                        false));
    // Init container
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                        cubeMesh, 
                                        multiLights, 
                                        {0.0f, 0.0f, 0.0f}, 
                                        settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f));
    // Init sphere
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                        sphereMesh,
                                        multiLights,
                                        {25.0f, 0.0f, 25.0f},
                                        settings.CONTAINER_RADIUS));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + rand()%30, 5.0f, 5 + rand()%30}, 
                                        settings.CONTAINER_RADIUS*0.3f,
                                        {.1f,.5f,.9f,.8f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + -rand()%30, 25.0f, 5 + rand()%30}, 
                                        settings.CONTAINER_RADIUS*0.3f,
                                        {.2f,.6f,1.0f,.7f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + -rand()%30, -5.0f, 5 + -rand()%30}, 
                                        settings.CONTAINER_RADIUS*0.3f,
                                        {.3f,.7f,.9f,.6f}));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {5 + rand()%30, 12.0f, 5 + -rand()%30}, 
                                        settings.CONTAINER_RADIUS*0.3f,
                                        {.4f,.8f,.7f,.5f}));

    EditorCamera camera = EditorCamera(vec3f({0.0f, 0.0f, 125.0f}), settings.WIDTH, settings.HEIGHT);
    Mouse mouse = Mouse();
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();

    m_fLastFrameTime = static_cast<float>(glfwGetTime());
    float theta = 0.0f;
    while (!Application::GetWindow()->ShouldClose()) 
    {
        /* Clears back buffer before new buffer is drawn */
        renderer->Clear();

        ProcessInput(mouse);

        camera.Update();

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0f / (static_cast<float>(glfwGetTime()) - m_fLastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(Application::GetGLFWwindow(), GLFW_KEY_V) == GLFW_PRESS 
            && m_totalModels < settings.MAX_INSTANCES) { }
        
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
        Application::GetWindow()->SwapBuffers();
        Application::GetWindow()->PollEvents();
        ClearErrors();
        DisplayStats();
        if (theta < 360 || theta >= 0) { 
            theta = theta + (60 * m_deltaTime); 
        }
        else { 
            theta = theta - (60 * m_deltaTime); 
        }
    }
}

void Application::DisplayStats() 
{
    GlobalSettings& settings = GlobalSettings::Instance();

    m_deltaTime = static_cast<float>(glfwGetTime()) - m_fLastFrameTime;
    while (m_deltaTime < 1.0f / settings.TARGET_FPS) {
        m_deltaTime = static_cast<float>(glfwGetTime()) - m_fLastFrameTime;
    }
    m_fLastFrameTime = static_cast<float>(glfwGetTime());
    m_totalFrames++;
    if (m_totalFrames % settings.TARGET_FPS == 0) { m_pWindow->UpdateWindowTitle(m_deltaTime, m_totalModels); }
}

void Application::ProcessInput(Mouse& mouse)
{
    // Display all active errors and clear buffer
    ClearErrors();

    if (glfwGetKey(m_pWindow->GetWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) { 
        glfwSetWindowShouldClose(m_pWindow->GetWindowPtr(), true);
    }
    
    mouse.UpdateMouse(m_pWindow->GetWindowPtr(), mouse.GetX(), mouse.GetY());
}

void Application::ClearErrors() const
{
    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }
}