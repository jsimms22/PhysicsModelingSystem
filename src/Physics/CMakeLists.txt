set(PHYSICS_SRC 
    force.cpp
    force.hpp
)

add_library(Physics STATIC ${PHYSICS_SRC})
target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})