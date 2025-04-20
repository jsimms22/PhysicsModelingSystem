cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

# project(PhysicsModelSystem LANGUAGES C CXX)
project(PhysicsModelSystem C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build the app
add_executable(${PROJECT_NAME} 
    src/app.cpp
)

# Choose platform implementation
set(PLATFORM_IMPL_OS "Windows")
set(PLATFORM_IMPL_RENDER "OpenGL")

# Add src directory
add_subdirectory(src)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/GL/build/cmake)

set(STB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/include)
set(STB_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/libs)

# STB
add_library(STB STATIC IMPORTED GLOBAL)
set_target_properties(STB PROPERTIES
    IMPORTED_LOCATION ${STB_LIB_DIR}/stbdll.a
    INTERFACE_INCLUDE_DIRECTORIES ${STB_INCLUDE_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC vendor/GLFW/include
    PUBLIC vendor/GL/include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC vendor/GLFW/src
    PUBLIC vendor/GL/src
    PUBLIC STB
    PUBLIC src
)