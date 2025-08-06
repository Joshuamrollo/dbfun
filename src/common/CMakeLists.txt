add_library(
    common STATIC
    QueryResult.cpp
)

target_include_directories(
    common PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)
