add_library(
    page STATIC
    PageUtils.cpp
    PageHeader.cpp
)

target_include_directories(
    page PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

