add_library(
    execution_engine STATIC
    ExecutionEngine.cpp
)

target_include_directories(
    execution_engine PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

