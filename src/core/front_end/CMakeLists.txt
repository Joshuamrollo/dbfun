add_library(
    front_end STATIC
    FrontEnd.cpp
)

target_link_libraries(
    front_end PRIVATE
    sqlparser)

target_include_directories(
    front_end PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)