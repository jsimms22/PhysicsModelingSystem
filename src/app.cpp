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
    
    std::vector<std::shared_ptr<Model>> modelContainer;
    // Init floor
    std::shared_ptr<Model> floor = std::make_shared<Model>(floorMesh,
                                                           settings.CONTAINER_RADIUS * 2 + settings.VERLET_RADIUS * 3,
                                                           GL_TRIANGLES);
    floor->SetPosition({0.0f, -(settings.CONTAINER_RADIUS * 2 + settings.VERLET_RADIUS * 3), 0.0f});
    floor->SetShader(baseShader);
    floor->SetIsPhysicalized(false);
    modelContainer.push_back(floor);

    // Init container
    std::shared_ptr<Model> container = std::make_shared<Model>(cubeMesh,
                            settings.CONTAINER_RADIUS * 2 + settings.VERLET_RADIUS * 3, 
                            GL_POINTS);
    container->SetShader(lightShader);
    container->SetIsPhysicalized(false);
    modelContainer.push_back(container);

    // Init sphere
    std::shared_ptr<Model> sphere = std::make_shared<Model>(sphereMesh,
                                                            settings.CONTAINER_RADIUS,
                                                            GL_TRIANGLES);
    sphere->SetShader(baseShader);
    sphere->SetIsPhysicalized(false);
    modelContainer.push_back(sphere);

    // Init light cube
    std::shared_ptr<Light> envLight = std::make_shared<Light>(sphereMesh,
                                                              settings.CONTAINER_RADIUS*0.3,
                                                              GL_TRIANGLES);
    envLight->SetShader(lightShader);
    envLight->SetIsPhysicalized(false);
    envLight->SetPosition(vec3f({15.0f, 15.0f, 10.0f}));
    envLight->SetColor(vec4f({0.9f, 0.9f, 0.8f, 1.0f}));

    // Init camera
    Camera camera = Camera(vec3f({0.0, 0.0, 125.0}), settings.WIDTH, settings.HEIGHT);
    // Init mouse
    Mouse mouse = Mouse();
    // Simulation stats
    std::size_t totalFrames = 0;
    std::size_t numActive = 0;
    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Display all active errors and clear buffer
    ClearErrors();

    while (!MainAppWnd->ShouldClose()) {
        /*-------*/
        /* Input */
        /*-------*/
        MainAppWnd->ProcessInput(); // determine if user is attempting to close window
        mouse.UpdateMouse(MainAppWnd->GetWindowPtr(), mouse.GetX(), mouse.GetY()); // update mouse position
        // std::cout << mouse.GetX() << ", " << mouse.GetY() << std::endl;
    
        /* Clears back buffer before new buffer is drawn */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Update env lighting position */
        envLight->UpdatePosition(MainAppWnd->GetWindowPtr()); // use arrow keys
        /* Update camera position */
        camera.ResetCamera(MainAppWnd->GetWindowPtr()); // checks if user wants to reset camera to initial position
        camera.UpdatePosition(MainAppWnd->GetWindowPtr());  // use wasd + shift + ctrl

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/
        baseShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateMatrix(45.0, 0.1, 1000.0);
        camera.UpdateUniform(baseShader->ID, "view");
        camera.UpdateUniform(baseShader->ID, "projection");
        camera.UpdateUniform(baseShader->ID, "camPos");
        
        // Exports uniforms needed for lighting updates
        envLight->UpdateUniform(baseShader->ID, "lightColor");
        envLight->UpdateUniform(baseShader->ID, "lightPos");
        baseShader->Detach();

        lightShader->Attach();
        // Updates and exports uniforms for camera
        camera.UpdateMatrix(45.0, 0.1, 1000.0);
        camera.UpdateUniform(lightShader->ID, "view");
        camera.UpdateUniform(lightShader->ID, "projection");
        // Exports uniforms needed for lighting updates
        envLight->UpdateUniform(lightShader->ID, "lightColor");
        lightShader->Detach();

        // Determine if we can add more entities for stress testing physics calculations
        // TODO: Move to a command system that does not rely on the game loop frame time
        if (1.0 / (static_cast<float>(glfwGetTime()) - lastFrameTime) >= settings.TARGET_FPS - 5 
            && glfwGetKey(MainAppWnd->GetWindowPtr(), GLFW_KEY_V) == GLFW_PRESS 
            && numActive < settings.MAX_INSTANCES) { 
            numActive += settings.ADDITION_SPEED;
            if (modelContainer.size() < numActive)
            {
                // Init sphere
                modelContainer.push_back(std::make_shared<Model>(sphereMesh, settings.CONTAINER_RADIUS, GL_TRIANGLES));
                float size = static_cast<float>(modelContainer.size());
                modelContainer.back()->SetShader(baseShader);
                modelContainer.back()->SetPosition({size*sphere->GetScale()*2,20,0});
            }
        }

        /*----------------------------*/
        /* force and position updates */
        /*----------------------------*/

        // TODO: implement euler/verlet and scale force vector for dt (frame generation time)
        for (std::shared_ptr<Model> i_model : modelContainer) {
            if (!i_model->IsPhysicalized()) { continue; }
            
        
            // Apply simple gravity to the balls
            vec3f result;
            //vec3_scale(settings.gravityVec, static_cast<float>(glfwGetTime()) - lastFrameTime ,settings.gravityVec);
            vec3_add(result, settings.gravityVec, i_model->GetPosition());
            
            // Only apply normal gravity vector if the model would not clip into the or be below the floor
            if (((i_model->GetPosition().data[1] - i_model->GetScale()) > floor->GetPosition().data[1]) && (result.data[1] - i_model->GetScale()) >= floor->GetPosition().data[1])
            {
                i_model->SetPosition(result);
            } else {
                // If model's bounds has fallen below the floor reset position to floor.y + .5*model height
                result.data[1] = floor->GetPosition().data[1] + i_model->GetScale();
                i_model->SetPosition(result);
            }
            
            // Apply simple collision to the balls
            /*
            for (std::shared_ptr<Model> j_model : modelContainer) {
                if (i_model == j_model) { continue; }
                // Check for collision
                if (i_model.isColliding(j_model)) {
                    // Apply the collision force response
                    i_model.applyCollisionForce(j_model);

                    // Output new velocities after collision
                    std::cout << "Collision Detected!\n";
                    std::cout << "Sphere 1 velocity: (" << sphere1.velocity.x << ", " << sphere1.velocity.y << ", " << sphere1.velocity.z << ")\n";
                    std::cout << "Sphere 2 velocity: (" << sphere2.velocity.x << ", " << sphere2.velocity.y << ", " << sphere2.velocity.z << ")\n";
                }

                // Update positions based on velocities (simple simulation)
                i_model.position = i_model.position + i_model.velocity;
                j_model.position = j_model.position + j_model.velocity;
            }
            */
        }

        /*----------------*/
        /* Render objects */
        /*----------------*/
        // TODO: include light into model container, need to properly virtualize base/child model classes and add OnUpdate etc methods
        DrawModelMesh(envLight,false);
        for (std::shared_ptr<Model> model : modelContainer) {
            DrawModelMesh(model,false);
        }
                 
        /*----------------------*/
        /* Clean Up and Measure */
        /*----------------------*/
        MainAppWnd->SwapBuffers();
        MainAppWnd->PollEvents();

        // Display all active errors and clear buffer
        ClearErrors();

        // Timing
        DisplayStats(MainAppWnd->GetWindowPtr(), totalFrames, lastFrameTime, numActive);
    }
    // Clean up shaders
    baseShader->Destroy();
    lightShader->Destroy();

    return 0;
}