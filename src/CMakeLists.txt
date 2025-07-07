add_subdirectory(common)
add_subdirectory(core/storage/file_format)
add_subdirectory(core/storage/io_manager)

add_executable(klikedb main.cpp)

target_link_libraries(
    klikedb PRIVATE 
    common 
    file_format
    io_manager)

target_include_directories(
    klikedb PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)
