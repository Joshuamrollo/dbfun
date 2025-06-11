add_library(
    common STATIC
    BitOperations.cpp
)

target_include_directories(
    common PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)
