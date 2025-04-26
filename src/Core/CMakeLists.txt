# Collect sources for this module
set(CORE_SRC 
    Application.cpp
    Application.hpp
    Input.hpp
    Window.cpp
    Window.hpp
)

# Create a library for this module
add_library(Core STATIC ${CORE_SRC})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Core PRIVATE app_vendor_deps)