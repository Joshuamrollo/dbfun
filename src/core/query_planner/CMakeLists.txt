add_library(
    query_planner STATIC
    QueryPlanner.cpp
    Optimizer.cpp
    Rewriter.cpp
    Binder.cpp
)

target_link_libraries(
    query_planner PRIVATE 
    common)

target_include_directories(
    query_planner PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/sql-parser)

