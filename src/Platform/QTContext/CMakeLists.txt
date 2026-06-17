# src/Platform/QT6Context/CMakeLists.txt

set(QT6Context_SRC
    QT6Input.cpp
    QT6Window.cpp
    QT6Window.hpp
)

add_library(QT6Context OBJECT ${QT6Context_SRC})

target_include_directories(QT6Context PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QT6Context
    PUBLIC
        glad
        glfw
        opengl32
        app_vendor_deps
        Core
        Events
)

target_compile_features(QT6Context PUBLIC cxx_std_23)