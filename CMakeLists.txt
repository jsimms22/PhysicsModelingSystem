## CONFIGURE CMAKE ##
cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## SET OUTPUT DIRECTORIES ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## CHOOSE PLATFORM IMPL ##
set(PLATFORM_IMPL_OS "Windows")
set(PLATFORM_IMPL_RENDER "OpenGL")

## ESTABLISH PROJECT ##
project(PhysicsModelSystem LANGUAGES CXX)

## BUILD APP ##
include_directories(
    vendor/GL/include/
    vendor/GLM/glm/
    vendor/GLFW/include/
    vendor/STB/include/
)

add_subdirectory(src)
add_subdirectory(vendor)

add_executable(app app.cpp)

target_link_libraries(app
    Core
    ECS
    Events
    Physics
    ${PLATFORM_IMPL_OS}
    ${PLATFORM_IMPL_RENDER}
    Renderer
    Scene
    Types
    Utils
    app_vendor_deps
)