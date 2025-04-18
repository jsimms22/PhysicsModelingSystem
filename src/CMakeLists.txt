# Add each domain/module as a subdirectory
add_subdirectory(Core)
add_subdirectory(ECS)
add_subdirectory(Events)
add_subdirectory(Physics)
add_subdirectory(Renderer)
add_subdirectory(Scene)
add_subdirectory(Types)
add_subdirectory(Utils)
# ...add others as needed

set(SOURCES
    app.cpp
)

# Build the app
add_executable(app ${SOURCES})

# Link everything together
target_link_libraries(app
    PRIVATE
        Core
        ECS
        Events
        Physics
        Renderer
        ${PLATFORM_IMPL_OS}
        ${PLATFORM_IMPL_RENDER}
        Scene
        Types
        Utils
        GLEW
        GLFW
        STB
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)