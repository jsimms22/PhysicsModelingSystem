# src/Scene/CMakeLists.txt

set(SCENE_SRC
    GeometryGenerator.hpp
    Model.cpp
    Model.hpp
    Scene.cpp
    Scene.hpp
)

add_library(Scene OBJECT ${SCENE_SRC})

target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Scene
    PUBLIC
        glad
        glfw
        opengl32
        tinyxml2
        glm::glm
        app_vendor_deps
        Renderer
        ECS
)

target_compile_features(Scene PUBLIC cxx_std_23)