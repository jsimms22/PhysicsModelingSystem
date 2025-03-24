// std library
#include <iostream>
#include <array>
#include <vector>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "../include/fwd_math.hpp"      // Contains M_PI constant
#include "../include/graphics.hpp"
#include "../include/hardware_input.hpp"
#include "../include/shaderClass.hpp"
#include "../include/cameraClass.hpp"
#include "../include/modelClass.hpp"
#include "../include/utility.hpp"       // Contains target fps global constant

// Compile-Time Constants
constexpr unsigned int WIDTH {1280};
constexpr unsigned int HEIGHT {1280};
constexpr unsigned int ADDITION_SPEED {10};
constexpr float CONTAINER_RADIUS {6.0};
constexpr float ENV_LIGHT_RADIUS {CONTAINER_RADIUS*0.3};
constexpr float VERLET_RADIUS {0.15};

int main()
{
    // Initialize GLFW
    if (!glfwInit()) { 
        std::cout << "GLFW init failure" << std::endl;
        return 1;
    }

    // Tells GLFW what version of opengl we are using: 3.3.0 NVIDIA 552.44
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we only want the modern functions via core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Title", NULL, NULL);
    if (!window) { 
        std::cout << "Terminating the window" << std::endl;
        glfwTerminate(); 
        return 1; 
    }

    // Assign a current OpenGL context
    glfwMakeContextCurrent(window);
    // allows glew to initialize GL
    auto iResult = glewInit();
    if (iResult != GLEW_OK) {
        std::cout << "GLew init falure" << std::endl;
        glfwTerminate();
        return 1;
    }
    // std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    /* OpenGL Settings */
    glfwSwapInterval(1);
    glViewport(0, 0, WIDTH, HEIGHT);        // Defines where we want glfw to render
    glClearColor(0.07f, 0.13f, 0.17f, 1.0); // Clears back buffer and renders new background
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3.0);

    // Shaders
    Shader baseShader = Shader("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");
    Shader lightShader = Shader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
    
    // Meshes
    std::shared_ptr<Mesh> cubeMesh = std::make_shared<Mesh>("models/cube.obj", false);
    std::shared_ptr<Mesh> sphereMesh = std::make_shared<Mesh>("models/sphere.obj", false);
    std::shared_ptr<Mesh> floorMesh = std::make_shared<Mesh>(floorVertex(100, 10, 10), floorIndex(100));
    
    // Init floor
    Model floor = Model(floorMesh,
                        CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3, 
                        GL_TRIANGLES,
                        {0.0f, -(CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3), 0.0f});

    // Init container
    Model container = Model(cubeMesh,
                            CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3, 
                            GL_POINTS);

    // Init sphere
    Model sphere = Model(sphereMesh,
                         CONTAINER_RADIUS, 
                         GL_TRIANGLES);

    // Init light cube
    Light envLight = Light(sphereMesh,
                           ENV_LIGHT_RADIUS, 
                           GL_TRIANGLES, 
                           vec4f({0.9f, 0.9f, 0.8f, 1.0f}),
                           vec3f({15.0f, 15.0f, 10.0f}));

    // Init camera
    vec3f cameraPos = { 0.0, 0.0, 125.0 };
    Camera camera = Camera(cameraPos, WIDTH, HEIGHT);
    // Init mouse
    Mouse mouse = Mouse();
    // Simulation stats
    int totalFrames = 0;
    int numActive = 0;
    float lastFrameTime = static_cast<float>(glfwGetTime());

    // Display all active errors and clear buffer
    clearErrors();

    while (!glfwWindowShouldClose(window)) {
        /*-------*/
        /* Input */
        /*-------*/
        processInput(window); // determine if user is attempting to close window
        mouse.updateMouse(window, mouse.getPosX(), mouse.getPosY()); // update mouse position
        // std::cout << mouse.getPosX() << ", " << mouse.getPosY() << std::endl;
    
        /* Clears back buffer before new buffer is drawn */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Update env lighting position */
        envLight.UpdatePosition(window); // use arrow keys
        /* Update camera position */
        camera.resetCamera(window); // checks if user wants to reset camera to initial position
        camera.inputs(window);  // use wasd + shift + ctrl

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/
        baseShader.attach();
        // Updates and exports uniforms for camera
        camera.updateMatrix(45.0, 0.1, 1000.0);
        camera.updateUniform(baseShader.ID, "view");
        camera.updateUniform(baseShader.ID, "projection");
        camera.updateUniform(baseShader.ID, "camPos");
        
        // Exports uniforms needed for lighting updates
        envLight.UpdateUniform(baseShader.ID, "lightColor");
        envLight.UpdateUniform(baseShader.ID, "lightPos");
        baseShader.detach();

        lightShader.attach();
        // Updates and exports uniforms for camera
        camera.updateMatrix(45.0, 0.1, 1000.0);
        camera.updateUniform(lightShader.ID, "view");
        camera.updateUniform(lightShader.ID, "projection");
        // Exports uniforms needed for lighting updates
        envLight.UpdateUniform(lightShader.ID, "lightColor");
        lightShader.detach();

        // Determine if we can add more entities for stress testing physics calculations
        if (1.0 / (static_cast<float>(glfwGetTime()) - lastFrameTime) >= TARGET_FPS - 5 
            && glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS 
            && numActive < MAX_INSTANCES) 
        { numActive += ADDITION_SPEED; }

        /*----------------------------*/
        /* force and position updates */
        /*----------------------------*/
        // force();

        /*----------------*/
        /* Render objects */
        /*----------------*/
        drawMesh(envLight.GetMesh(), lightShader, envLight.GetRenderMethod(), 
                 envLight.GetPosition(), envLight.GetRotation(), envLight.GetScale());
        drawMesh(container.GetMesh(), lightShader, container.GetRenderMethod(), 
                 container.GetPosition(), container.GetRotation(), container.GetScale());
        drawMesh(sphere.GetMesh(), baseShader, sphere.GetRenderMethod(), 
                 sphere.GetPosition(), sphere.GetRotation(), sphere.GetScale());
        drawMesh(floor.GetMesh(), baseShader, floor.GetRenderMethod(), 
                 floor.GetPosition(), floor.GetRotation(), floor.GetScale());
                 
        /*----------------------*/
        /* Clean Up and Measure */
        /*----------------------*/
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Display all active errors and clear buffer
        clearErrors();

        // Timing
        displayStats(window, totalFrames, lastFrameTime, numActive);
    }
    // Clean up shaders
    baseShader.destroy();
    // Terminate window and glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}