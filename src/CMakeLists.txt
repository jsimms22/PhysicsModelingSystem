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