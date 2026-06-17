# src/CMakeLists.txt

#add_library(PhysicsModelSystem SHARED) 
add_library(PhysicsModelSystem STATIC)

# Add each domain/module as a subdirectory
add_subdirectory(Core)
add_subdirectory(ECS)
add_subdirectory(Events)
add_subdirectory(Physics)
add_subdirectory(Renderer)
add_subdirectory(Scene)
add_subdirectory(Types)
add_subdirectory(Utils)
add_subdirectory(Platform/${PLATFORM_IMPL_OS})
add_subdirectory(Platform/${PLATFORM_IMPL_RENDER})
# ...add others as needed

target_sources(PhysicsModelSystem 
    PRIVATE
        $<TARGET_OBJECTS:Core>
        $<TARGET_OBJECTS:ECS>
        $<TARGET_OBJECTS:Events>
        $<TARGET_OBJECTS:Physics>
        $<TARGET_OBJECTS:Renderer>
        $<TARGET_OBJECTS:Scene>
        $<TARGET_OBJECTS:Types>
        $<TARGET_OBJECTS:${PLATFORM_IMPL_OS}>
        $<TARGET_OBJECTS:${PLATFORM_IMPL_RENDER}>
)

target_link_libraries(PhysicsModelSystem
    PRIVATE
        glfw
        glad
        glm::glm
        opengl32
)