// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../types.hpp"
#include "../Core/Application.hpp"
#include "../Core/globalSettings.hpp"    // Contains our settings singleton 
#include "../Core/mouseClass.hpp"
#include "../Core/windowClass.hpp"
#include "../Core/sys_callbacks.hpp"
#include "../Physics/force.hpp"
#include "../Renderer/graphics.hpp"
#include "../Renderer/shaderClass.hpp"
#include "../Scene/cameraClass.hpp"
#include "../Scene/modelClass.hpp"
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
    std::shared_ptr<Shader> instanceShader = std::make_shared<Shader>("shaders/instance_vertex.glsl", "shaders/base_fragment.glsl");
        
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj");
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj");
    std::shared_ptr<Mesh> floorMesh = std::make_shared<Mesh>(FloorVertex(100, 10, 10), FloorIndex(100));
    
    std::vector<std::shared_ptr<IModel>> modelContainer;
    // Init floor terrain
    /*
    modelContainer.push_back(CreateModelFactory(ModelType::Terrain, 
                                                floorMesh, 
                                                baseShader, 
                                                {0.0f, -(settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f), 0.0f}, 
                                                settings.CONTAINER_RADIUS * 2.0f + settings.VERLET_RADIUS * 3.0f));
    */
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
    modelContainer.back()->AddMesh(lightShader, "lightColor");

    // Init camera
    Camera camera = Camera(vec3f({0.0f, 0.0f, 125.0f}), settings.WIDTH, settings.HEIGHT);
    
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

        /* Camera Input */
        camera.ResetCamera(GetWindow()->GetWindowPtr()); // checks if user wants to reset camera to initial position
        // Update camera position, view, projection matrices
        camera.UpdatePosition(GetWindow()->GetWindowPtr());  // use wasd + shift + ctrl
        camera.UpdateMatrix(45.0f, 0.1f, 10000.0f);

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/
        baseShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateUniform(baseShader->GetID(), "cameraMatrix");
        camera.UpdateUniform(baseShader->GetID(), "camPos");
        baseShader->Detach();

        lightShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateUniform(lightShader->GetID(), "cameraMatrix");
        lightShader->Detach();

        instanceShader->Attach();
        camera.UpdateUniform(instanceShader->GetID(),"cameraMatrix");
        camera.UpdateUniform(instanceShader->GetID(), "camPos");
        instanceShader->Detach();
        
        for (std::shared_ptr<IModel> model : modelContainer) { model->Update(); }

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0f / (static_cast<float>(glfwGetTime()) - m_fLastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(GetWindow()->GetWindowPtr(), GLFW_KEY_V) == GLFW_PRESS 
            && m_totalModels < settings.MAX_INSTANCES) 
        { 
            m_totalModels += settings.ADDITION_SPEED;

            if (modelContainer.size() < m_totalModels)
            {
                std::vector<mat4x4f> translations;
                for (std::size_t itr = 0; itr < settings.ADDITION_SPEED; ++itr) {
                    float x = rand() * 25;
                    float radius = settings.CONTAINER_RADIUS;
                    float y = ((rand() % 2) * 2 - 1) * sqrt(1.0f - x * x);

                    vec3f tempTranslation;
                    vec3f tempRotation;
                    float tempScale = 1.0f;

                    // Makes the random distribution more even
                    if (randf() > 0.5f)
                    {
                        // Generates a translation near a circle of radius "radius"
                        tempTranslation = {y * radius, randf(), x * radius};
                    }
                    else
                    {
                        // Generates a translation near a circle of radius "radius"
                        tempTranslation = {x * radius, randf(), y * radius};
                    }

                    struct {
                        mat4x4f position;
                        mat4x4f rotation;
                        mat4x4f scaling;
                        mat4x4f model;
                    } matrices;
                
                    /* Position */
                    mat4x4_id(matrices.position);
                    mat4x4_translation(matrices.position, matrices.position, tempTranslation);
                
                    /* Rotation */
                    mat4x4_id(matrices.rotation);
                    mat4_eulerAngles(matrices.rotation, tempRotation);
                
                    /* Scaling */
                    mat4x4_id(matrices.scaling);
                    mat4x4_buildScaler(matrices.scaling, matrices.scaling, vec3f{tempScale,tempScale,tempScale});

                    /* Model matrix */
                    mat4x4_mul(matrices.model, matrices.rotation, matrices.scaling);
                    mat4x4_mul(matrices.model, matrices.position, matrices.model);

                    translations.push_back(matrices.model);
                }

                std::shared_ptr<Mesh> instanceMesh = std::make_shared<Mesh>("models/sphere.obj", settings.ADDITION_SPEED, translations);

                // Init sphere
                modelContainer.push_back(CreateModelFactory(ModelType::Shape, 
                                                            std::move(instanceMesh), 
                                                            baseShader));
            }
        }

        /*----------------------------*/
        /* force and position updates */
        /*----------------------------*/
        // TODO: implement euler for gravity and collisions
        // ApplyForces(modelContainer);

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