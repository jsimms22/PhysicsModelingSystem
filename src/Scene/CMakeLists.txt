set(SCENE_SRC
    Model.cpp
    Model.hpp
    Scene.cpp
    Scene.hpp
)

add_library(Scene STATIC ${SCENE_SRC})
target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Scene
    PRIVATE
        glad
        glfw
        opengl32
        tinyxml2
        Renderer
        ECS
)