// std library
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// project headers
#include "../include/fwd_math.hpp"
#include "../include/graphics.hpp"
#include "../include/hardware_input.hpp"
#include "../include/shaders.hpp"
#include "../include/camera.hpp"
#include "../include/model.hpp"
#include "../include/lighting.hpp"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

// Compile-Time Constants
constexpr unsigned int WIDTH {1280};
constexpr unsigned int HEIGHT {1280};
constexpr unsigned int ADDITION_SPEED {10};
constexpr unsigned int TARGET_FPS {144};
constexpr float CONTAINER_RADIUS {6.0};
constexpr float ENV_LIGHT_RADIUS {CONTAINER_RADIUS*0.3};
constexpr float VERLET_RADIUS {0.15};
constexpr float CAM_RADIUS {24.0};

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
    /* Set up a callback function for when the window is resized */
    glfwSwapInterval(1);

    /* OpenGL Settings */
    glViewport(0, 0, WIDTH, HEIGHT);    // Defines where we want glfw to render
    glClearColor(0.07f, 0.13f, 0.17f, 1.0);   // Clears back buffer and renders new background
    glClearStencil(0);

    glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE); glCullFace(GL_BACK); glFrontFace(GL_CCW);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3.0);

    /* Models & Shaders */
    unsigned int baseShader = createShader("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");
    if (baseShader == 0) { std::cout << "baseShader creation failed." << std::endl; return 0;}
    unsigned int phongShader = createShader("shaders/phong_vertex.glsl", "shaders/phong_fragment.glsl");
    if (phongShader == 0) { std::cout << "phongShader creation failed." << std::endl; return 0;};
    unsigned int lightShader = createShader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
    if (lightShader == 0) { std::cout << "lightShader creation failed." << std::endl; return 0;};


    Meshf cubeMesh = createMesh("models/cube.obj", false);
    Meshf lightMesh = createMesh("models/sphere.obj", false);
    Meshf sphereMesh = createMesh("models/sphere.obj", false);

    // World stats
    vec3f origin{ 0.0, 0.0, 0.0 };
    // Init container
    vec3f containerPosition{ 0.0, 0.0, 0.0 };
    vec3f rotation{ 0.0, 0.0, 0.0 }; 
    // Init light cube
    vec3f lightPosition{ 5.0, 5.0, -5.0 };
    vec4f lightColor = { 0.9, 0.9, 0.8 , 1.0 };
    Lighting envLight = Lighting(lightPosition, lightColor, lightMesh);
    envLight.setScale(ENV_LIGHT_RADIUS);
    // Init camera
    vec3f initial_pos = { 0.0, 0.0, CAM_RADIUS*3 };
    Camera camera = Camera(initial_pos, WIDTH, HEIGHT);
    // Init mouse
    Mouse mouse = Mouse();
    // Window stats
    int totalFrames = 0;
    int numActive = 0;
    float dt = 0.000001f;
    float lastFrameTime = static_cast<float>(glfwGetTime());
    char title[100] = "";

    // Display all active errors and clear buffer
    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }

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
        envLight.input(window); // use arrow keys
        /* Update camera position */
        camera.resetCamera(window); // checks if user wants to reset camera to initial position
        camera.inputs(window);  // use wasd + shift + ctrl

        /*-----------------*/
        /* Shader Uniforms */
        /*-----------------*/
        glUseProgram(baseShader);
        // Updates and exports uniforms for camera
        camera.updateMatrix(45.0, 0.1, 1000.0);
        camera.updateUniform(baseShader, "view");
        camera.updateUniform(baseShader, "projection");
        // Exports uniforms needed for lighting updates
        glUniform4f(glGetUniformLocation(baseShader, "lightColor"), 
            envLight.color.data[0], envLight.color.data[1], envLight.color.data[2], envLight.color.data[3]);
        glUniform3f(glGetUniformLocation(baseShader, "lightPos"), 
             envLight.position.data[0], envLight.position.data[1], envLight.position.data[2]);
        glUniform3f(glGetUniformLocation(baseShader, "camPos"), 
            camera.position.data[0], camera.position.data[1], camera.position.data[2]);
        glUseProgram(0);

        glUseProgram(lightShader);
        // Updates and exports uniforms for camera
        camera.updateMatrix(45.0, 0.1, 1000.0);
        camera.updateUniform(lightShader, "view");
        camera.updateUniform(lightShader, "projection");
        // Exports uniforms needed for lighting updates
        glUniform4f(glGetUniformLocation(lightShader, "lightColor"), lightColor.data[0], lightColor.data[1], lightColor.data[2], lightColor.data[3]);
        glUseProgram(0);

        if (1.0 / dt >= TARGET_FPS - 5 && glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && numActive < MAX_INSTANCES) {
            numActive += ADDITION_SPEED;
        }
 
        if (totalFrames % 60 == 0) {
            sprintf(title, "FPS : %-4.0f | Balls : %-10d", 1.0 / dt, numActive);
            glfwSetWindowTitle(window, title);
        }

        // force and position updates
        
        /*----------------*/
        /* Render objects */
        /*----------------*/
        drawMesh(envLight.mesh, lightShader, GL_TRIANGLES, envLight.position, rotation, envLight.scale);
        drawMesh(cubeMesh, lightShader, GL_POINTS, containerPosition, rotation, CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3);
        drawMesh(sphereMesh, baseShader, GL_TRIANGLES, origin, rotation, CONTAINER_RADIUS);
        // drawMesh(cubeMesh, baseShader, GL_TRIANGLES, origin, rotation, CONTAINER_RADIUS);

        /*----------------------*/
        /* Clean Up and Measure */
        /*----------------------*/
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Display all active errors and clear buffer
        while (glGetError() != GL_NO_ERROR) {
            std::cout << glGetError() << std::endl;
        }

        // Timing
        dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
        while (dt < 1.0f / TARGET_FPS) {
            dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
        }
        lastFrameTime = static_cast<float>(glfwGetTime());
        totalFrames++;
    }
    // Clean up shaders
    destroyShader(baseShader);
    // Terminate window and glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}