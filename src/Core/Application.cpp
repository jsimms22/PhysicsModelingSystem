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
#include "../Core/Window.hpp"
#include "../Core/sys_callbacks.hpp"
#include "../Physics/force.hpp"
#include "../Renderer/Graphics.hpp"
#include "../Renderer/Shader.hpp"
#include "../Renderer/EditorCamera.hpp"
#include "../Scene/Model.hpp"
#include "../Utils/utility.hpp"
// std library
#include <iostream>
#include <array>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

float randf()
{
	return -1.0f + (rand() / (RAND_MAX / 2.0f));
}

// Define the static member variable outside the class
std::weak_ptr<Application> Application::s_instance;

Application::Application()
{
    WindowProps props{};
    m_pWindow = std::make_unique<Window>(props);
}

void Application::Run()
{
    GlobalSettings& settings = GlobalSettings::Instance();

    // Shaders
    std::shared_ptr<Shader> baseShader = std::make_shared<Shader>("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");
    std::shared_ptr<Shader> multiLights = std::make_shared<Shader>("shaders/multiple_vertex.glsl", "shaders/multiple_fragment.glsl");
    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
    //std::shared_ptr<Shader> instanceShader = std::make_shared<Shader>("shaders/instance_vertex.glsl", "shaders/base_fragment.glsl");
        
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj");
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj");
    std::shared_ptr<Mesh> floorMesh = std::make_shared<Mesh>(FloorVertex(100, 10, 10), FloorIndex(100));
    
    std::vector<std::shared_ptr<IModel>> models;
    std::vector<std::shared_ptr<IModel>> lights;
    // Init floor terrain
    models.push_back(CreateModelFactory(ModelType::Terrain, 
                                                floorMesh, 
                                                multiLights, 
                                                {0.0f, -(settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f), 0.0f}, 
                                                100.0f,
                                                GL_TRIANGLES,
                                                false));
    // Init container
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                                cubeMesh, 
                                                multiLights, 
                                                {0.0f, 0.0f, 0.0f}, 
                                                settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f,
                                                GL_TRIANGLES,
                                                false));
    // Init sphere
    models.push_back(CreateModelFactory(ModelType::Shape, 
                                                sphereMesh, 
                                                multiLights, 
                                                {0.0f, 0.0f, 0.0f}, 
                                                settings.CONTAINER_RADIUS,
                                                GL_TRIANGLES,
                                                false));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        cubeMesh, 
                                        lightShader, 
                                        {25.0f, 5.0f, 25.0f}, 
                                        settings.CONTAINER_RADIUS*0.3f));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        sphereMesh, 
                                        lightShader, 
                                        {-25.0f, 25.0f, 25.0f}, 
                                        settings.CONTAINER_RADIUS*0.3f));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        sphereMesh, 
                                        lightShader, 
                                        {-25.0f, -5.0f, -25.0f}, 
                                        settings.CONTAINER_RADIUS*0.3f));
    // Init light cube
    lights.push_back(CreateModelFactory(ModelType::Light, 
                                        sphereMesh, 
                                        lightShader, 
                                        {25.0f, 12.0f, -25.0f}, 
                                        settings.CONTAINER_RADIUS*0.3f));

    // Init camera
    EditorCamera camera = EditorCamera(vec3f({0.0f, 0.0f, 125.0f}), settings.WIDTH, settings.HEIGHT);
    // Init mouse
    Mouse mouse = Mouse();
    // Simulation stats
    m_fLastFrameTime = static_cast<float>(glfwGetTime());
    // Display all active errors and clear buffer
    Application::GetWindow()->ClearErrors();

    vec4f randomLight{};
    float lightIncrement = 0.01f;

    while (!Application::GetWindow()->ShouldClose()) {
        /* Input */
        Application::GetWindow()->ProcessInput();
        mouse.UpdateMouse(Application::GetGLFWwindow(), mouse.GetX(), mouse.GetY());
    
        /* Clears back buffer before new buffer is drawn */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Update camera position, view, projection matrices
        camera.Update();
        
        /* Shader Uniforms */
        
        // Multiple Lights Shader Lighting
        // directional light:
        multiLights->SetUniform4fm("cameraMatrix", camera.GetCameraMatrix());
        multiLights->SetUniform3fv("cameraPosition", camera.GetPosition());
        multiLights->SetUniform3fv("dirLight.position", {-0.2f, -1.0f, -0.3f});
        multiLights->SetUniform3fv("dirLight.ambient", {0.05f, 0.05f, 0.05f});
        multiLights->SetUniform3fv("dirLight.diffuse", {0.4f, 0.4f, 0.4f});
        multiLights->SetUniform3fv("dirLight.specular", {0.5f, 0.5f, 0.5f});
        // spotlight

        std::size_t lightIndex {};
        for (std::shared_ptr<IModel> light : lights) 
        {   
            // Modifying the color of the light
            for (std::size_t i = std::floor(rand()%4); i < 4; ++i) {
                randomLight[i] += lightIncrement;
                if (randomLight[i] >= 1) { 
                    lightIncrement = -lightIncrement; 
                } else if (randomLight[i] <= 0) {
                    lightIncrement = -lightIncrement; 
                }
            }
            vec4f result{};
            vec4_add(result, randomLight, light->GetColor());

            {   // Multiple Lights Shader Lighting
                multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].position", light->GetPosition());
                multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].ambient", {0.05f, 0.05f, 0.05f});
                multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].diffuse", {0.8f, 0.8f, 0.8f});
                multiLights->SetUniform3fv("pointLights[" + std::to_string(lightIndex) + "].specular", {1.0f, 1.0f, 1.0f});
                multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].constant", 1.0f);
                multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].linear", 0.04f);
                multiLights->SetFloat("pointLights[" + std::to_string(lightIndex) + "].quadratic", 0.0075f);
                ++lightIndex;
            }
        }
        multiLights->SetUniform4fv("lightColor", lights.back()->GetColor());
        // Base Shader Lighting - 1 only light is calculates so just use the last one
        baseShader->SetUniform4fv("lightColor", lights.back()->GetColor());
        baseShader->SetUniform3fv("lightPosition", lights.back()->GetPosition());
        baseShader->SetUniform4fm("cameraMatrix", camera.GetCameraMatrix());
        baseShader->SetUniform3fv("cameraPosition", camera.GetPosition());
        // Light Shader Lighting - all lights are the same so use the last one
        lightShader->SetUniform4fv("lightColor", lights.back()->GetColor());
        lightShader->SetUniform4fm("cameraMatrix", camera.GetCameraMatrix());

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0f / (static_cast<float>(glfwGetTime()) - m_fLastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(Application::GetGLFWwindow(), GLFW_KEY_V) == GLFW_PRESS 
            && m_totalModels < settings.MAX_INSTANCES) { }
        
        for (std::shared_ptr<IModel> light : lights) 
        {   
            light->Update();
            vec3f result{};
            vec3_add(result, {randomLight[1],randomLight[2],randomLight[3]}, light->GetRotation());
            light->SetScale(light->GetScale() + lightIncrement * 2);
            light->SetRotation(result);
            DrawModelMesh(light); 
        }

        /* Render objects */
        // TODO: implement proper virtual model class and concrete classes
        for (std::shared_ptr<IModel> model : models) 
        {   
            model->Update(); 
            DrawModelMesh(model); 
        }
                 
        /* Clean Up and Measure */
        Application::GetWindow()->SwapBuffers();
        Application::GetWindow()->PollEvents();
        Application::GetWindow()->ClearErrors();
        Application::GetWindow()->DisplayStats(m_totalFrames, m_fLastFrameTime, m_totalModels);
    }
}