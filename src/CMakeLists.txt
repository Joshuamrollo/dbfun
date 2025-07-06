add_subdirectory(common)
add_subdirectory(core/storage)

add_executable(klikedb main.cpp)

target_link_libraries(
    klikedb PRIVATE 
    common 
    storage)

target_include_directories(
    klikedb PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)
