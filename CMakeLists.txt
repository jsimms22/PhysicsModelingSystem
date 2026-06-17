# root/CMakeLists.txt

## CONFIGURE CMAKE ##
cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

## ESTABLISH PROJECT ##
project(PhysicsModelSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

## ----- GLAD ----- ##
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)

## ----- TinyXML ----- ##
set(tinyxml2_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_Declare(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
)
FetchContent_MakeAvailable(tinyxml2)

## ------ GLM ------ ##
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

## SET OUTPUT DIRECTORIES ##
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## CHOOSE PLATFORM IMPL ##
set(PLATFORM_IMPL_OS "GLFWContext")
set(PLATFORM_IMPL_RENDER "OpenGL")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

## ----- Build and Configure ----- ##
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
   AND CMAKE_BUILD_TYPE STREQUAL "Debug")
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

# for doing test runs
add_executable(app app.cpp)
target_link_libraries(app PhysicsModelSystem)

# Post build commands
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/models
        $<TARGET_FILE_DIR:app>/models
)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:app>/shaders
)