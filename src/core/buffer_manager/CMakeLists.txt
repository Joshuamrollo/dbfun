add_library(
    buffer_manager STATIC
    BufferManager.cpp
)

target_include_directories(
    buffer_manager PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

