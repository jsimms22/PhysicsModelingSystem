set(TYPES_SRC 
    GUID.cpp
    GUID.hpp
    mat3x3.hpp
    mat4x4.hpp
    vec2.hpp
    vec3.hpp
    vec4.hpp
    vertex.hpp
)

add_library(Types STATIC ${TYPES_SRC})
target_include_directories(Types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})