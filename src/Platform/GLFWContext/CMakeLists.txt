# src/Platform/GLFWContext/CMakeLists.txt

set(GLFWContext_SRC
    GLFWInput.cpp
    GLFWWindow.cpp
    GLFWWindow.hpp
)

add_library(GLFWContext OBJECT ${GLFWContext_SRC})

target_include_directories(GLFWContext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GLFWContext
    PUBLIC
        glad
        glfw
        opengl32
        app_vendor_deps
        Core
        Events
)

target_compile_features(GLFWContext PUBLIC cxx_std_23)