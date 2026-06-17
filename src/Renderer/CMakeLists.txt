# src/Renderer/CMakeLists.txt

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

add_library(Renderer OBJECT ${RENDER_SRC})

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Renderer
    PUBLIC
        glad
        glfw
        opengl32
        glm::glm
        app_vendor_deps
        Events
)

target_compile_features(Renderer PUBLIC cxx_std_23)