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
#include "../include/math.hpp"
#include "../include/graphics.hpp"
#include "../include/hardware_input.hpp"
#include "../include/shaders.hpp"
#include "../include/camera.hpp"
#include "../include/sys_callbacks.hpp"
#include "../include/model.hpp"
#include "../include/utility.hpp"

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

// Compile-Time Constants
constexpr unsigned int WIDTH {1280};
constexpr unsigned int HEIGHT = {720};
constexpr unsigned int ADDITION_SPEED {10};
constexpr unsigned int TARGET_FPS {144};
constexpr float CONTAINER_RADIUS {6.0};
constexpr float VERLET_RADIUS {0.15};
constexpr float cameraRadius {12.0};

// Vertices coordinates
float vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
unsigned int indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

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
        return -1; 
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

    Meshf cubeMesh = createMeshFromFile("models/cube.obj", false);

    // Container
    vec3f containerPosition{ 0.0, 0.0, 0.0 };
    vec3f rotation{ 0.0, 0.0, 0.0 }; 

    int totalFrames = 0;
    int numActive = 0;

    float dt = 0.000001f;
    float lastFrameTime = static_cast<float>(glfwGetTime());

    char title[100] = "";

    vec3f initial_pos = { 0.0, 0.0, cameraRadius*3 };
    Camera camera = Camera(WIDTH, HEIGHT, initial_pos);
    Mouse mouse = Mouse();

    while (glGetError() != GL_NO_ERROR) {
        std::cout << glGetError() << std::endl;
    }

    while (!glfwWindowShouldClose(window)) {
        /* INPUT */
        mouse.updateMouse(window, mouse.getPosX(), mouse.getPosY()); // update mouse position
        // std::cout << mouse.getPosX() << ", " << mouse.getPosY() << std::endl;
        processInput(window); // determine if user is attempting to close window

        // Clears back buffer before new buffer is drawn
        glClearColor(0.07f, 0.13f, 0.17f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        /* Shader Uniforms */
        glUseProgram(baseShader);
        camera.viewMatrix(45.0, 0.1, 100.0, baseShader);
        glUseProgram(0);
        glUseProgram(phongShader);
        camera.viewMatrix(45.0, 0.1, 100.0, phongShader);
        glUseProgram(0);

        if (1.0 / dt >= TARGET_FPS - 5 && glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && numActive < MAX_INSTANCES) {
            numActive += ADDITION_SPEED;
        }
 
        if (totalFrames % 60 == 0) {
            sprintf(title, "FPS : %-4.0f | Balls : %-10d", 1.0 / dt, numActive);
            glfwSetWindowTitle(window, title);
        }

        // camera key captures
        camera.inputs(window);

        // force and position updates
        
        /* Container */
        drawMesh(cubeMesh, baseShader, GL_TRIANGLES, containerPosition, rotation, CONTAINER_RADIUS * 2 /*+ VERLET_RADIUS * 3*/);
        // drawMesh(cubeMesh, baseShader, GL_POINTS, containerPosition, rotation, CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3);

        // Swaps back buffer with front buffer
        while (glGetError() != GL_NO_ERROR) {
            std::cout << glGetError() << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        /* Timing */
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