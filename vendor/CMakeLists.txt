find_package(OpenGL REQUIRED)

add_subdirectory(GL/build/cmake)
add_subdirectory(GLFW)

## STB ##
set(STB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/include)
set(STB_LIB_DIR ${CMAKE_SOURCE_DIR}/vendor/STB/libs)
add_library(STB STATIC IMPORTED GLOBAL)
set_target_properties(STB PROPERTIES
    IMPORTED_LOCATION ${STB_LIB_DIR}/stbdll.a
    INTERFACE_INCLUDE_DIRECTORIES ${STB_INCLUDE_DIR}
)

add_library(app_vendor_deps INTERFACE)

target_link_libraries(app_vendor_deps INTERFACE
    glew
    glfw3
    STB
)
