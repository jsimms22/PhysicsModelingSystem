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
constexpr size_t WIDTH = 640;
constexpr size_t HEIGHT = 640;

// Sample shader file text buffers
const GLchar* vertexSource =
"#version 450\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";
const GLchar* fragmentSource =
"#version 450\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

int main()
{
    GLFWwindow* window;
    if (!glfwInit()) { 
        std::cout << "GLFW init failure" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    Meshf mesh = createMesh("models/sphere.obj", false);

    // Create Vertex Buffer
    std::array<Vertex3f,6> vertices =
    {
        /* FRONT PANEL */
        Vertex3(vec3f{ -0.5f,  0.5f,  0.5f }, vec3f{ 1.0f, 0.0f, 0.0f }), // Top-Left
        Vertex3(vec3f{  0.5f,  0.5f,  0.5f }, vec3f{ 0.0f, 1.0f, 0.0f }), // Top-right
        Vertex3(vec3f{  0.5f, -0.5f,  0.5f }, vec3f{ 0.0f, 0.0f, 1.0f }), // Bottom-right
        // ...
        Vertex3(vec3f{  0.5f, -0.5f,  0.5f }, vec3f{ 0.0f, 0.0f, 1.0f }), // Bottom-right
        Vertex3(vec3f{ -0.5f, -0.5f,  0.5f }, vec3f{ 0.0f, 1.0f, 0.0f }), // Bottom-left
        Vertex3(vec3f{ -0.5f,  0.5f,  0.5f }, vec3f{ 1.0f, 0.0f, 0.0f }), // Top-left
    };

    // Create and Bind Vertex Buffers (vertices)
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    /*
    std::array<GLuint,6> elements = {
        0, 1, 2,
        2, 3, 0
    };

    // Create and Bind Element Buffers (elements)
    GLuint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements.data(), GL_STATIC_DRAW);
    */

    // Vertex Shader Calls
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexSource, NULL);
    glCompileShader(vertex_shader);

    // Fragment Shader Calls
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(fragment_shader);

    // Link the vertex and fragment shader into a shader program
    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint posAttrib = glGetAttribLocation(program, "vPos");
    const GLint colAttrib = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex3f), reinterpret_cast<void*>(offsetof(Vertex3f, position)));

    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex3f), reinterpret_cast<void*>(offsetof(Vertex3f, color)));

    Mouse mouse = Mouse();

    while (!glfwWindowShouldClose(window)) {
        /* INPUT */
        mouse.updateMouse(window, mouse.getPosX(), mouse.getPosY()); // update mouse position
        processInput(window); // determine if user is attempting to close window

        // std::cout << "glfw is initialized" << std::endl;
        
        float ratio;
        int width, height;
        mat4x4f m, p, mvp;
 
        glfwGetFramebufferSize(window, &width, &height);
        ratio = static_cast<float>(width) / static_cast<float>(height);
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        mat4x4_id(m);
        mat4x4_rotate_Z(m, m, static_cast<float>(glfwGetTime()));
        mat4x4_rotate_X(m, m, static_cast<float>(glfwGetTime()));
        mat4x4_rotate_Y(m, m, static_cast<float>(glfwGetTime()));
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
        
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(mvp.data));
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}