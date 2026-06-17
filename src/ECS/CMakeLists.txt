# src/ECS/CMakeLists.txt

set(ECS_SRC 
    ComponentManager.cpp
    ComponentManager.hpp
    Components.cpp
    Components.hpp
    Entity.cpp
    Entity.hpp
    EntityManager.cpp
    EntityManager.hpp
)

add_library(ECS OBJECT ${ECS_SRC})

target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ECS
    PUBLIC
)

target_compile_features(ECS PUBLIC cxx_std_23)
