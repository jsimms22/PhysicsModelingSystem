// std library
#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <memory>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"
// ../include
#include "../include/camera.hpp"
#include "../include/graphics.hpp"
#include "../include/shaders.hpp"
#include "../include/math.hpp"
#include "../include/hardware_input.hpp"
#include "../include/custom_types.hpp"

using vec2f = vec2<float>;
using vec2d = vec2<double>;

using vec3f = vec3<float>;
using vec3d = vec3<double>;

using Vertexf = Vertex<float>;
using Vertexd = Vertex<double>;

static inline const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static inline const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
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
    
    window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
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
    glfwSwapInterval(1); 

    // Create Vertex Buffer
    std::array<Vertexf,3> vertices =
    {
        Vertexf(vec2f{ -0.6f, -0.4f }, vec3f{ 1.0f, 0.0f, 0.0f }),
        Vertexf(vec2f{  0.6f, -0.4f }, vec3f{ 0.0f, 1.0f, 0.0f }),
        Vertexf(vec2f{  0.0f,  0.6f }, vec3f{ 0.0f, 0.0f, 1.0f })
    };

    // NOTE: OpenGL error checks have been omitted for brevity
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertexf), reinterpret_cast<void*>(offsetof(Vertexf, pos)));

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertexf), reinterpret_cast<void*>(offsetof(Vertexf, col)));

    Mouse mouse = Mouse();

    while (!glfwWindowShouldClose(window)) {
        /* INPUT */
        mouse.updateMouse(window, mouse.getPosX(), mouse.getPosY()); // update mouse position
        processInput(window); // determine if user is attempting to close window

        // std::cout << "glfw is initialized" << std::endl;

        float ratio;
        int width, height;
        mat4x4 m, p, mvp;
 
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_rotate_X(m, m, (float) glfwGetTime());
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
 
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();

    return 0;
}