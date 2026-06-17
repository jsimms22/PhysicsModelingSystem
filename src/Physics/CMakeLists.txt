# src/Physics/CMakeLists.txt

set(PHYSICS_SRC 
    force.cpp
    force.hpp
)

add_library(Physics OBJECT ${PHYSICS_SRC})

target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Physics
    PUBLIC
        glm::glm
        app_vendor_deps
)

target_compile_features(Physics PUBLIC cxx_std_23)