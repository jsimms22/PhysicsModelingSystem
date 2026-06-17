# src/Types/CMakeLists.txt

set(TYPES_SRC 
    GUID.cpp
    GUID.hpp
    Shapes.hpp
    vertex.hpp
)

add_library(Types OBJECT ${TYPES_SRC})

target_include_directories(Types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Renderer
    PUBLIC
        glm::glm
        app_vendor_deps
)

target_compile_features(Types PUBLIC cxx_std_23)