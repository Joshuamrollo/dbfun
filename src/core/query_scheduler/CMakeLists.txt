add_library(
    query_scheduler STATIC
    QueryScheduler.cpp
)

target_include_directories(
    query_scheduler PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

