set(MATH_SRC 
    math.hpp
)

add_library(EngineMath STATIC ${MATH_SRC})
target_include_directories(EngineMath PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})