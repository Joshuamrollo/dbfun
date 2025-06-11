# Add subdirectories for components
add_subdirectory(common)
add_subdirectory(core/storage)

# Build the main executable
add_executable(klikedb main.cpp)

# Link with internal libraries
target_link_libraries(
    klikedb PRIVATE 
    common 
    storage)

# Include path for all targets
target_include_directories(
    klikedb PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)
