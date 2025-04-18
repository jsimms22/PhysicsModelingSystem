set(RENDER_SRC 
    Camera.hpp
    EditorCamera.cpp
    EditorCamera.hpp
    ElementBuffer.cpp
    ElementBuffer.hpp
    graphics.cpp
    graphics.hpp
    GraphicsContext.cpp
    GraphicsContext.hpp
    Mesh.cpp
    Mesh.hpp
    RenderAPI.cpp
    RenderAPI.hpp
    RenderCommand.cpp
    RenderCommand.hpp
    Renderer.cpp
    Renderer.hpp
    Shader.cpp
    Shader.hpp
    Texture.cpp
    Texture.hpp
    VertexArray.cpp
    VertexArray.hpp
    VertexBuffer.cpp
    VertexBuffer.hpp
)

add_library(Renderer STATIC ${RENDER_SRC})

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Renderer
    PRIVATE
        Events
        ${PLATFORM_IMPL_OS}
        ${PLATFORM_IMPL_RENDER}
        GLEW
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)