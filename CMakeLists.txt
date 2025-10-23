## CONFIGURE CMAKE ##
cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_print_variables(CMAKE_BUILD_TYPE)

## SET OUTPUT DIRECTORIES ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## CHOOSE PLATFORM IMPL ##
set(PLATFORM_IMPL_OS "Windows")
cmake_print_variables(PLATFORM_IMPL_OS)
set(PLATFORM_IMPL_RENDER "OpenGL")
cmake_print_variables(PLATFORM_IMPL_RENDER)

## ESTABLISH PROJECT ##
project(PhysicsModelSystem LANGUAGES CXX)

## BUILD APP ##
include_directories(
    vendor/GL/include/
    vendor/GLM/glm/
    vendor/GLFW/include/
    vendor/STB/include/
)

add_subdirectory(vendor)
# Add general compile options
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)
add_subdirectory(src)

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