set(QT6Context_SRC
    QT6Input.cpp
    QT6Window.cpp
    QT6Window.hpp
)

add_library(QT6Context_SRC STATIC ${QT6Context_SRC})

target_include_directories(QT6Context_SRC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QT6Context_SRC
    PRIVATE
        glad
        glfw
        opengl32
        Core
        Events
)