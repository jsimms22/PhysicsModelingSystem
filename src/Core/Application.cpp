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

float randf()
{
	return -1.0f + (rand() / (RAND_MAX / 2.0f));
}

Application::Application()
{
    m_pInstance = Application::Get();

    WindowProps props{};

    m_pWindow = std::make_unique<Window>(props);
}

void Application::Run()
{
    GlobalSettings& settings = GlobalSettings::Instance();

    // Shaders
    std::shared_ptr<Shader> baseShader = std::make_shared<Shader>("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");
    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
    //std::shared_ptr<Shader> instanceShader = std::make_shared<Shader>("shaders/instance_vertex.glsl", "shaders/base_fragment.glsl");
        
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj");
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj");
    std::shared_ptr<Mesh> floorMesh = std::make_shared<Mesh>(FloorVertex(100, 10, 10), FloorIndex(100));
    
    std::vector<std::shared_ptr<IModel>> modelContainer;
    // Init floor terrain
    modelContainer.push_back(CreateModelFactory(ModelType::Terrain, 
                                                floorMesh, 
                                                baseShader, 
                                                {0.0f, -(settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f), 0.0f}, 
                                                settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f));
    // Init container
    modelContainer.push_back(CreateModelFactory(ModelType::Shape, 
                                                cubeMesh, 
                                                lightShader, 
                                                {0.0f, 0.0f, 0.0f}, 
                                                settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f,
                                                GL_POINTS));
    // Init sphere
    modelContainer.push_back(CreateModelFactory(ModelType::Shape, 
                                                sphereMesh, 
                                                baseShader, 
                                                {0.0f, 0.0f, 0.0f}, 
                                                settings.CONTAINER_RADIUS,
                                                GL_TRIANGLES,
                                                false));
    // Init light cube
    modelContainer.push_back(CreateModelFactory(ModelType::Light, 
                                                sphereMesh, 
                                                lightShader, 
                                                {15.0f, 15.0f, 10.0f}, 
                                                settings.CONTAINER_RADIUS*0.3f));
    modelContainer.back()->AddMesh(baseShader, "lightColor");
    modelContainer.back()->AddMesh(baseShader, "lightPosition");
    modelContainer.back()->AddMesh(lightShader, "lightColor");

    // Init camera
    EditorCamera camera = EditorCamera(vec3f({0.0f, 0.0f, 125.0f}), settings.WIDTH, settings.HEIGHT);
    
    // Init mouse
    Mouse mouse = Mouse();

    // Simulation stats
    m_fLastFrameTime = static_cast<float>(glfwGetTime());

    // Display all active errors and clear buffer
    GetWindow()->ClearErrors();

    while (!GetWindow()->ShouldClose()) {
        /*-------*/
        /* Input */
        /*-------*/
        GetWindow()->ProcessInput();
        mouse.UpdateMouse(GetWindow()->GetWindowPtr(), mouse.GetX(), mouse.GetY());
    
        /* Clears back buffer before new buffer is drawn */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Update camera position, view, projection matrices
        camera.ResetCamera(GetWindow()->GetWindowPtr()); // checks if user wants to reset camera to initial position
        camera.UpdatePosition(GetWindow()->GetWindowPtr());  // use wasd + shift + ctrl
        camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/
        baseShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateUniform(baseShader->GetID(), "cameraMatrix");
        camera.UpdateUniform(baseShader->GetID(), "cameraPosition");
        baseShader->Detach();

        lightShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateUniform(lightShader->GetID(), "cameraMatrix");
        lightShader->Detach();
        
        for (std::shared_ptr<IModel> model : modelContainer) { model->Update(); }

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0f / (static_cast<float>(glfwGetTime()) - m_fLastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(GetWindow()->GetWindowPtr(), GLFW_KEY_V) == GLFW_PRESS 
            && m_totalModels < settings.MAX_INSTANCES) 
        {
        }

        /*----------------*/
        /* Render objects */
        /*----------------*/
        // TODO: implement proper virtual model class and concrete classes
        for (std::shared_ptr<IModel> model : modelContainer) { DrawModelMesh(model); }
                 
        /*----------------------*/
        /* Clean Up and Measure */
        /*----------------------*/
        GetWindow()->SwapBuffers();
        GetWindow()->PollEvents();
        GetWindow()->ClearErrors();
        GetWindow()->DisplayStats(m_totalFrames, m_fLastFrameTime, m_totalModels);
    }
}