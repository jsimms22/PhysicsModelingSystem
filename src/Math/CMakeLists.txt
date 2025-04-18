set(MATH_SRC 
    math.hpp
)

add_library(Math STATIC ${MATH_SRC})
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})