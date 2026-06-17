# src/Utils/CMakeLists.txt

set(UTILS_SRC
    utility.cpp
    utility.hpp
)

add_library(Utils STATIC ${UTILS_SRC})

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Utils
    PUBLIC
)

target_compile_features(Utils PUBLIC cxx_std_23)