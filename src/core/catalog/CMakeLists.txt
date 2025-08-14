add_library(
    catalog STATIC
    Catalog.cpp
)

target_include_directories(
    catalog PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

