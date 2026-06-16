set(GLFWContext_SRC
    GLFWInput.cpp
    GLFWWindow.cpp
    GLFWWindow.hpp
)

add_library(GLFWContext STATIC ${GLFWContext_SRC})

target_include_directories(GLFWContext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GLFWContext
    PRIVATE
        glad
        glfw
        opengl32
        Core
        Events
)