cmake_minimum_required(VERSION 3.14)
project(klikedb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/sql-parser)
add_subdirectory(src/core/front_end)
add_subdirectory(src/core/query_planner)
add_subdirectory(src/core/query_scheduler)
add_subdirectory(src/core/catalog)
add_subdirectory(src/core/file_format)
add_subdirectory(src/core/io_manager)
add_subdirectory(src/core/buffer_manager)

add_executable(my_database
    src/main.cpp
)

target_link_libraries(my_database
    sqlparser
    front_end
    query_planner
    query_scheduler
    catalog
    file_format
    io_manager
    buffer_manager
)