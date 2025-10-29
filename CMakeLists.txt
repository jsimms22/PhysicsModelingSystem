## CONFIGURE CMAKE ##
cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CMakePrintHelpers)
include(FetchContent)

## ----- GLFW ----- ##
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_MakeAvailable(glfw)
## ----- GLFW ----- ##

## ----- GLAD ----- ##
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)
## ----- GLAD ----- ##

## ----- TinyXML ----- ##
set(tinyxml2_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_Declare(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
)
FetchContent_MakeAvailable(tinyxml2)
## ----- TinyXML ----- ##

## SET OUTPUT DIRECTORIES ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## CHOOSE PLATFORM IMPL ##
set(PLATFORM_IMPL_OS "Windows")
set(PLATFORM_IMPL_RENDER "OpenGL")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

## ESTABLISH PROJECT ##
project(PhysicsModelSystem LANGUAGES CXX)

## ----- Build and Configure ----- ##
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Add general compile options
    add_compile_options(-Wall
                        -Wextra
                        -Wshadow
                        -Wnon-virtual-dtor
                        -Wold-style-cast
                        -Wcast-align
                        -Wunused
                        -Woverloaded-virtual
                        -Wpedantic
                        -Wconversion
                        -Wsign-conversion
                        -Wnull-dereference
                        -Wdouble-promotion
                        -Wformat=2
                        -Wduplicated-cond
                        -Wduplicated-branches
                        -Wlogical-op
                        -Wuseless-cast)
endif()

add_subdirectory(vendor)
add_subdirectory(src)

add_executable(app app.cpp)

target_link_libraries(app
    glad
    glfw
    opengl32
    tinyxml2
    app_vendor_deps
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
)