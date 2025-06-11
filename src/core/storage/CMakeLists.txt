# Add page subdirectory
add_subdirectory(page)

add_library(
    storage STATIC
    BufferPool.cpp
    DiskScheduler.cpp
    IOManager.cpp
)

# Link against page and common (assuming storage depends on them)
target_link_libraries(
    storage PRIVATE
    page
    common
)

target_include_directories(
    storage PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)
