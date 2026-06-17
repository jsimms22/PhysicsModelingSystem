# src/Core/CMakeLists.txt

# Collect sources for this module
set(CORE_SRC
    Application.cpp
    Application.hpp
    Input.hpp
    Window.cpp
    Window.hpp
    WindowAPI.cpp
    WindowAPI.hpp
)

# Create a library for this module
add_library(Core OBJECT ${CORE_SRC})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Core
    PUBLIC
        glad
        glfw
        glm::glm
        opengl32
        app_vendor_deps
)

target_compile_features(Core PUBLIC cxx_std_23)