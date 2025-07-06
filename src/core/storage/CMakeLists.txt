add_subdirectory(file_format)

add_library(
    storage STATIC
    temp.cpp
)

target_link_libraries(
    storage PRIVATE
    file_format
    common
)

target_include_directories(
    storage PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)
