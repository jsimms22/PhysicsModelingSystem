set(OPENGL_SRC
    OpenGLContext.cpp
    OpenGLContext.hpp
    OpenGLRenderAPI.cpp
    OpenGLRenderAPI.hpp
)

add_library(OpenGL STATIC ${OPENGL_SRC})

target_include_directories(OpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenGL
    PRIVATE
        glad
        glfw
        opengl32
        Renderer
)