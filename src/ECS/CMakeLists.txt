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

add_library(ECS STATIC ${ECS_SRC})
target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})