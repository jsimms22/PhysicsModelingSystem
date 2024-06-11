// std library
#include <iostream>
#include <array>
#include <vector>
#include <memory>
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

// Compile-Time Constants
constexpr unsigned int WIDTH {1280};
constexpr unsigned int HEIGHT = {720};
constexpr unsigned int ADDITION_SPEED {10};
constexpr unsigned int TARGET_FPS {144};
#define CONTAINER_RADIUS 6.0f
#define VERLET_RADIUS 0.15f

int main()
{
    GLFWwindow* window;
    if (!glfwInit()) { 
        std::cout << "GLFW init failure" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; // 3.3.0 NVIDIA 552.44

    window = glfwCreateWindow(WIDTH, HEIGHT, "My Title", NULL, NULL);
    if (!window) { 
        std::cout << "Terminating the window" << std::endl;
        glfwTerminate(); 
        return 1; 
    }

    glfwMakeContextCurrent(window); // assigns a current OpenGL context
    auto iResult = glewInit();      // allows glew to initialize GL
    if (iResult != GLEW_OK) {       // ensure gl inits
        std::cout << "GLew init falure" << std::endl;
        glfwTerminate();            // otherwise end glfw proc
        return 1; 
    }
    /* Set up a callback function for when the window is resized */
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    /* Callback function for mouse enter/exit */
    // glfwSetCursorEnterCallback(window, cursor_enter_callback);

    /* OpenGL Settings */
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClearStencil(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(3.0);

    /* Models & Shaders */
    GLuint phongShader = createShader("shaders/phong_vertex.glsl", "shaders/phong_fragment.glsl");
    GLuint instanceShader = createShader("shaders/instance_vertex.glsl", "shaders/instance_fragment.glsl");
    GLuint baseShader = createShader("shaders/base_vertex.glsl", "shaders/base_fragment.glsl");

    Meshf mesh = createMesh("models/sphere.obj", true);
    //Meshf cubeMesh = createMesh("models/cube.obj", false);
    
    //Modelf model = createModel(mesh);

    // Container
    vec4f containerPosition{ 1, 1, 1, 1 };
    vec4f rotation{ 1, 1, 1, 1 };

    int totalFrames = 0;
    int numActive = 10;
    float view[16];

    float dt = 0.000001f;
    float lastFrameTime = static_cast<float>(glfwGetTime());

    char title[100] = "";

    srand(time(NULL));

    Mouse mouse = Mouse();

    while (!glfwWindowShouldClose(window)) {
        // std::cout << "glfw is initialized" << std::endl;
        /* INPUT */
        mouse.updateMouse(window, mouse.getPosX(), mouse.getPosY()); // update mouse position
        // std::cout << mouse.getPosX() << ", " << mouse.getPosY() << std::endl;
        processInput(window); // determine if user is attempting to close window
        
        /* Shader Uniforms */
        glUseProgram(phongShader);
        glUniformMatrix4fv(glGetUniformLocation(phongShader, "view"), 1, GL_FALSE, view);
        glUseProgram(0);
        glUseProgram(baseShader);
        glUniformMatrix4fv(glGetUniformLocation(baseShader, "view"), 1, GL_FALSE, view);
        glUseProgram(0);
        glUseProgram(instanceShader);
        glUniformMatrix4fv(glGetUniformLocation(instanceShader, "view"), 1, GL_FALSE, view);
        glUseProgram(0);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (1.0 / dt >= TARGET_FPS - 5 && glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && numActive < MAX_INSTANCES) {
            numActive += ADDITION_SPEED;
        }
 
        if (totalFrames % 60 == 0) {
            sprintf(title, "FPS : %-4.0f | Balls : %-10d", 1.0 / dt, numActive);
            glfwSetWindowTitle(window, title);
        }

        // camera key captures

        // force and position updates

        glBindBuffer(GL_ARRAY_BUFFER, mesh.positionVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * INSTANCE_STRIDE * numActive, mesh.vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mesh.velocityVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * numActive, mesh.vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /* Draw instanced verlet objects */
        drawInstanced(mesh, instanceShader, GL_TRIANGLES, numActive, 1);

        /* Container */
        // drawMesh(cubeMesh, baseShader, GL_TRIANGLES, containerPosition, rotation, CONTAINER_RADIUS * 2 + VERLET_RADIUS * 3);
        // drawMesh(mesh, baseShader, GL_TRIANGLES, containerPosition, rotation, 0.1);
        // drawMesh(mesh, baseShader, GL_POINTS, containerPosition, rotation, 0.1);

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
    
    glfwTerminate();

    return 0;
}