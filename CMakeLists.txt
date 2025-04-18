cmake_minimum_required(VERSION 3.30)

project(PhysicsModelSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set paths to the static .a lib and headers
set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/GL/include)
set(GLEW_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/GL/libs)

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/GLFW/include)
set(GLFW_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/GLFW/libs)

set(STB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/include)
set(STB_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/libs)

# OPENGL
add_library(GLEW STATIC IMPORTED GLOBAL)
set_target_properties(GLEW PROPERTIES
    IMPORTED_LOCATION ${GLEW_LIB_DIR}/libglew32.a
    INTERFACE_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIR}
)

# GLFW
add_library(GLFW STATIC IMPORTED GLOBAL)
set_target_properties(GLFW PROPERTIES
    IMPORTED_LOCATION ${GLFW_LIB_DIR}/libglfw3.a
    INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIR}
)

# STB
add_library(STB STATIC IMPORTED GLOBAL)
set_target_properties(STB PROPERTIES
    IMPORTED_LOCATION ${STB_LIB_DIR}/stbdll.a
    INTERFACE_INCLUDE_DIRECTORIES ${STB_INCLUDE_DIR}
)

# Choose platform implementation
set(PLATFORM_IMPL_OS "Windows")
add_subdirectory(src/Platform/${PLATFORM_IMPL_OS})

set(PLATFORM_IMPL_RENDER "OpenGL")
add_subdirectory(src/Platform/${PLATFORM_IMPL_RENDER})


# Manually link OpenGL (for Windows)
set(GLEW_LIBRARIES glew32)
set(GLFW_LIBRARIES glfw3)
set(OPENGL_LIBRARIES opengl32)

# Add src directory
add_subdirectory(src)