// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project headers
#include "Application.hpp"
#include "Input.hpp"
#include "Window.hpp"

#include "../Events/EventNotifier.hpp"
#include "../Events/Event.hpp"
#include "../Events/WindowEvents.hpp"
#include "../Events/ApplicationEvents.hpp"

#include "../Physics/force.hpp"

#include "../Renderer/EditorCamera.hpp"
#include "../Renderer/Graphics.hpp"
#include "../Renderer/Mesh.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/Texture.hpp"

#include "../Scene/Model.hpp"

#include "../Types/vec3.hpp"
#include "../Types/vertex.hpp"
// std library
#include <cmath>
#include <functional>
#include <string>
#include <utility>
#include <vector>

// Define the static member variable outside the class
std::weak_ptr<Application> Application::s_applicationInstance;

Application::Application(Private /*p*/)
{
    m_spWindow = IWindow::Create();
    m_spWindow->SetEventCallback([this](Event& e) -> void { this->OnEvent(e); });

    Renderer::Init();
}

void Application::OnEvent(Event& e)
{
    EventNotifier notifier(e);
    notifier.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& close) -> bool { return this->OnWindowClose(close); });
    notifier.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& resize) -> bool { return this->OnWindowResize(resize); });
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
#ifdef DEBUG
    std::cout << "Window resizing\n";
#endif //DEBUG

    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_bMinimized = true;
        return false;
    }

    m_bMinimized = false;

    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

bool Application::OnWindowClose(WindowCloseEvent& /*e*/)
{
#ifdef DEBUG
    std::cout << "Window closing\n";
#endif //DEBUG

    m_bRunning = false;
    return true;
}

std::shared_ptr<Application> Application::Create()
{
    if (auto instance = s_applicationInstance.lock())
    {
        return instance;
    }
    else
    {
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
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj");

    std::vector<std::shared_ptr<IModel>> models;
    std::vector<std::shared_ptr<IModel>> lights;
    // Init floor terrain
    models.push_back(CreateModelFactory(ModelType::Terrain, std::make_shared<Mesh>(FloorVertex(100, 5, 5), FloorIndex(100))));
    models.back()->SetShader(lightShader);
    models.back()->SetPosition({0.0, -12.0, 0.0});
    models.back()->SetScale(100.f);
    models.back()->SetRenderMethod(GL_LINES);
    models.back()->SetIsPhysicalized(false);

    // Init container
    models.push_back(CreateModelFactory(ModelType::Shape, cubeMesh));
    models.back()->SetShader(multiLights);
    models.back()->SetPosition({0.0, 0.0, 0.0});
    models.back()->SetScale(5.0f);
    models.back()->SetColor({1.0, 0.0, 0.0, 1.0});

    // Init sphere
    models.push_back(CreateModelFactory(ModelType::Shape, sphereMesh));
    models.back()->SetShader(multiLights);
    models.back()->SetPosition({25.0, 0.0, 0.0});
    models.back()->SetScale(2.0f);
    models.back()->SetColor({1.0, 1.0, 0.0, 1.0});

    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, sphereMesh));
    lights.back()->SetShader(lightShader);
    lights.back()->SetPosition({static_cast<double>(5 + rand()%30), 5.0, static_cast<double>(5 + rand()%30)});
    lights.back()->SetScale(1.0f);
    lights.back()->SetColor({0.1f, 0.5f, 0.9f, 1.f});

    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, sphereMesh));
    lights.back()->SetShader(lightShader);
    lights.back()->SetPosition({static_cast<double>(5 + -rand()%30), 25.0, static_cast<double>(5 + rand()%30)});
    lights.back()->SetScale(1.0f);
    lights.back()->SetColor({0.2f, 0.6f, 1.0f, 1.f});

    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, sphereMesh));
    lights.back()->SetShader(lightShader);
    lights.back()->SetPosition({static_cast<double>(5 + -rand()%30), -5.0, static_cast<double>(5 + -rand()%30)});
    lights.back()->SetScale(1.0f);
    lights.back()->SetColor({0.3f, 0.7f, 0.9f, 1.f});

    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, sphereMesh));
    lights.back()->SetShader(lightShader);
    lights.back()->SetPosition({static_cast<double>(5 + -rand()%30), 12.0f, static_cast<double>(5 + -rand()%30)});
    lights.back()->SetScale(1.0f);
    lights.back()->SetColor({0.4f, 0.8f, 0.7f, 1.f});

    const bool bUseDirLight = false;
    const bool bUseSpotLight = false;
    // Set up static directional light uniforms
    if (bUseDirLight)
    {
        multiLights->SetUniform3fv("dirLight.direction", {1.0f, 1.0f, 1.0f});
        multiLights->SetUniform4fv("dirLight.color", {1.0f, 1.0f, 1.0f, 1.0f});
        multiLights->SetUniform3fv("dirLight.ambient", {0.05f, 0.05f, 0.05f});
        multiLights->SetUniform3fv("dirLight.diffuse", {0.4f, 0.4f, 0.4f});
        multiLights->SetUniform3fv("dirLight.specular", {0.5f, 0.5f, 0.5f});
    }

    // Set up static spot light uniforms
    if (bUseSpotLight)
    {
        multiLights->SetUniform4fv("spotLight.color", {1.0f, 1.0f, 1.0f, 1.0f});
        multiLights->SetUniform3fv("spotLight.ambient", {0.0f, 0.0f, 0.0f});
        multiLights->SetUniform3fv("spotLight.diffuse", {1.0f, 1.0f, 1.0f});
        multiLights->SetUniform3fv("spotLight.specular", {1.0f, 1.0f, 1.0f});
        multiLights->SetFloat("spotLight.constant", 1.0f);
        multiLights->SetFloat("spotLight.linear", 0.09f);
        multiLights->SetFloat("spotLight.quadratic", 0.032f);
        multiLights->SetFloat("spotLight.cutOff", static_cast<float>(std::cos(0.2181662)));
        multiLights->SetFloat("spotLight.outerCutOff", static_cast<float>(std::cos(0.61799)));
    }

    // Set up static point light uniforms
    std::size_t lightIndex = 0;
    multiLights->SetInteger("numPointLights", static_cast<int>(lights.size()));
    for (std::shared_ptr<IModel> light : lights)
    {
        multiLights->SetUniform4fv("pointLights[" + std::to_string(lightIndex) + "].color", light->GetColor());
        multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].ambient", {0.05f, 0.05f, 0.05f});
        multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].diffuse", {0.8f, 0.8f, 0.8f});
        multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].specular", {1.f, 1.f, 1.f});
        multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].constant", 1.0f);
        multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].linear", 0.045f);
        multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].quadratic", 0.0075f);
        ++lightIndex;
    }

    EditorCamera camera = EditorCamera(vec3d({0.0, 0.0, 125.0}),
                                       static_cast<float>(m_spWindow->GetWidth()),
                                       static_cast<float>(m_spWindow->GetHeight()));
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();
    m_stats.lastFrameTime = glfwGetTime();
    double theta = 0.0;

#ifdef DEBUG
    std::cout << "Running\n";
#endif //DEBUG
    while (m_bRunning)
    {
        /* Clears back buffer before new buffer is drawn */
        Renderer::Clear();

        if (Input::IsKeyPressed(KeyCode::Escape)) { Application::Close(); }
        camera.UpdateViewport(static_cast<float>(m_spWindow->GetWidth()), static_cast<float>(m_spWindow->GetHeight()));
        camera.OnUpdate();

        /* Shader Uniforms */
        // Multiple Lights Shader Lighting
        multiLights->SetUniform4dm("cameraMatrix", camera.GetCameraMatrix());
        multiLights->SetUniform3dv("cameraPosition", camera.GetPosition());
        if (bUseSpotLight)
        {
            multiLights->SetUniform3dv("spotLight.position", camera.GetPosition());
            multiLights->SetUniform3fv("spotLight.direction", static_cast<vec3f>(camera.GetDirection()));
        }

        lightIndex = 0;
        for (std::shared_ptr<IModel> light : lights)
        {
            switch (lightIndex % 4)
            {
                case 0:
                {
                    light->SetPosition({-30.0*std::cos(theta * (PI/180.0)), light->GetPosition()[1], 30.0*std::sin(theta * (PI/180.0))});
                    break;
                }
                case 1:
                {
                    light->SetPosition({-30.0*std::cos(theta * (PI/180.0)), -30.0*std::sin(theta * (PI/180.0)), light->GetPosition()[2]});
                    break;
                }
                case 2:
                {
                    light->SetPosition({30.0*std::cos(theta * (PI/180.0)), light->GetPosition()[1], -30.0*std::sin(theta * (PI/180.0))});
                    break;
                }
                case 3:
                {
                    light->SetPosition({-30.0*std::cos(theta * (PI/180.0)), light->GetPosition()[1], -30.0*std::sin(theta * (PI/180.0))});
                    break;
                }
            }
            ++lightIndex;
        }

        lightIndex = 0;
        lightShader->SetUniform4dm("cameraMatrix", camera.GetCameraMatrix());
        for (std::shared_ptr<IModel> light : lights)
        {
            lightShader->SetUniform4fv("lightColor", light->GetColor());
            const auto data = renderer->DrawModelMesh(light);
            multiLights->SetUniform4dm("pointLights[" + std::to_string(lightIndex) + "].model", data.model);
            ++lightIndex;
        }

        for (std::shared_ptr<IModel> model : models)
        {
            multiLights->SetFloat("material.shininess", 0.4f);
            if (model->SupportsType(ModelType::Shape))
            {
                multiLights->SetUniform4fv("modelColor", model->GetColor());
            }
            else
            {
                // just using it for terrain for now since it is a static color
                lightShader->SetUniform4fv("lightColor", {1.0,1.0,1.0,0.5});
            }

            renderer->DrawModelMesh(model);
        }

        /* Clean Up and Measure */
        m_spWindow->OnUpdate();
#ifdef DEBUG
        ClearErrors();
#endif //DEBUG
        DisplayStats();

        if (theta < 360 || theta >= 0)
        {
            theta = theta + (60 * m_stats.deltaTime);
        }
        else
        {
            theta = theta - (60 * m_stats.deltaTime);
        }
    }
}

void Application::DisplayStats()
{
    m_stats.deltaTime = glfwGetTime() - m_stats.lastFrameTime;
    while (m_stats.deltaTime < (1.0 / static_cast<double>(m_stats.targetFPS))) {
        m_stats.deltaTime = glfwGetTime() - m_stats.lastFrameTime;
    }
    m_stats.lastFrameTime = glfwGetTime();
    m_stats.totalFrames++;
    if (m_stats.totalFrames % m_stats.targetFPS == 0) { m_spWindow->UpdateWindowTitle(m_stats.deltaTime, m_stats.totalModels); }
}

void Application::ClearErrors() const
{
    while (glGetError() != GL_NO_ERROR) {
        std::cout << "error code: " << glGetError() << std::endl;
    }
}

std::shared_ptr<Application> Application::GetApplication()
{
    // If we cannot return a valid instance, then
    // we should not create a new application
    return s_applicationInstance.lock();
}

Application::Statistics& Application::GetStats() { return m_stats; }

IWindow& Application::GetWindow() { return *m_spWindow; }

void Application::Close() { m_bRunning = false; }