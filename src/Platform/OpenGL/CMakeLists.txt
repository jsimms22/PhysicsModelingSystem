# src/Platform/OpenGL/CMakeLists.txt

set(OPENGL_SRC
    OpenGLContext.cpp
    OpenGLContext.hpp
    OpenGLRenderAPI.cpp
    OpenGLRenderAPI.hpp
)

add_library(OpenGL OBJECT ${OPENGL_SRC})

target_include_directories(OpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenGL
    PUBLIC
        glad
        glfw
        opengl32
        Renderer
)

target_compile_features(OpenGL PUBLIC cxx_std_23)