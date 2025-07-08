add_library(
    io_manager STATIC
    IOManager.cpp
)

target_link_libraries(
    io_manager PRIVATE 
    file_format)

target_include_directories(
    io_manager PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

