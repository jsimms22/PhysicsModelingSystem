// std library
#include <iostream>
#include <array>
#include <vector>
#include <stdexcept>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "../include/fwd_math.hpp"
#include "../include/graphics.hpp"
#include "../include/hardware_input.hpp"    // Contains GLFW and Window classes for now
#include "../include/shaderClass.hpp"
#include "../include/cameraClass.hpp"
#include "../include/modelClass.hpp"
#include "../include/utility.hpp"
#include "../include/globalSettings.hpp"    // Contains our settings singleton 
#include "../include/force.hpp"

int main()
{
    GlobalSettings& settings = GlobalSettings::Instance();
    std::unique_ptr<GLFWContext> GFLWInstance = std::make_unique<GLFWContext>();
    std::unique_ptr<Window> MainAppWnd = std::make_unique<Window>(GFLWInstance,settings.WIDTH,settings.HEIGHT, "My Window");

    // Shaders
    std::shared_ptr<Shader> baseShader = std::make_shared<Shader>("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");
    std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
        
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj", false);
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj", false);
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
    modelContainer.back()->AddMesh(baseShader, "lightPos");
    modelContainer.back()->AddMesh(lightShader,"lightColor");

    // Init camera
    Camera camera = Camera(vec3f({0.0f, 0.0f, 125.0f}), settings.WIDTH, settings.HEIGHT);
    // Init mouse
    Mouse mouse = Mouse();
    // Simulation stats
    std::size_t totalFrames = 0;
    std::size_t numActive = 0;
    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Display all active errors and clear buffer
    MainAppWnd->ClearErrors();

    while (!MainAppWnd->ShouldClose()) {
        /*-------*/
        /* Input */
        /*-------*/
        MainAppWnd->ProcessInput();
        mouse.UpdateMouse(MainAppWnd->GetWindowPtr(), mouse.GetX(), mouse.GetY());
    
        /* Clears back buffer before new buffer is drawn */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Update camera position */
        camera.ResetCamera(MainAppWnd->GetWindowPtr()); // checks if user wants to reset camera to initial position
        camera.UpdatePosition(MainAppWnd->GetWindowPtr());  // use wasd + shift + ctrl

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/

        baseShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);
        camera.UpdateUniform(baseShader->GetID(), "view");
        camera.UpdateUniform(baseShader->GetID(), "projection");
        camera.UpdateUniform(baseShader->GetID(), "camPos");
        baseShader->Detach();

        lightShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);
        camera.UpdateUniform(lightShader->GetID(), "view");
        camera.UpdateUniform(lightShader->GetID(), "projection");
        lightShader->Detach();
        
        for (std::shared_ptr<IModel> model : modelContainer) { model->Update(); }

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0f / (static_cast<float>(glfwGetTime()) - lastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(MainAppWnd->GetWindowPtr(), GLFW_KEY_V) == GLFW_PRESS 
            && numActive < settings.MAX_INSTANCES) { 
            numActive += settings.ADDITION_SPEED;
            
            if (modelContainer.size() < numActive)
            {
                // Init sphere
                modelContainer.push_back(CreateModelFactory(ModelType::Shape, 
                                                            sphereMesh, 
                                                            baseShader, 
                                                            {static_cast<float>(modelContainer.size()) * settings.CONTAINER_RADIUS*2,20,0}, 
                                                            settings.CONTAINER_RADIUS));
            }
        }

        /*----------------------------*/
        /* force and position updates */
        /*----------------------------*/
        // TODO: implement euler for gravity and collisions
        ApplyForces(modelContainer);

        /*----------------*/
        /* Render objects */
        /*----------------*/
        // TODO: implement proper virtual model class and concrete classes
        for (std::shared_ptr<IModel> model : modelContainer) { DrawModelMesh(model,false); }
                 
        /*----------------------*/
        /* Clean Up and Measure */
        /*----------------------*/
        MainAppWnd->SwapBuffers();
        MainAppWnd->PollEvents();
        MainAppWnd->ClearErrors();
        MainAppWnd->DisplayStats(totalFrames, lastFrameTime, numActive);
    }

    return 0;
}