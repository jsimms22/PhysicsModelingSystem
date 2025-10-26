set(WINDOWS_SRC
    WindowsInput.cpp
    WindowsWindow.cpp
    WindowsWindow.hpp
)

add_library(Windows STATIC ${WINDOWS_SRC})

target_include_directories(Windows PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Windows
    PRIVATE
        glad
        glfw
        opengl32
        Core
        Events
)