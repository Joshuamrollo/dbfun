cmake_minimum_required(VERSION 3.14)
project(klikedb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
