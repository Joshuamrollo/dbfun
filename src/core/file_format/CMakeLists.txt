find_library(LZ4_LIB lz4)

if (NOT LZ4_LIB)
  message(FATAL_ERROR "lz4 library not found")
endif()

add_library(
    file_format STATIC
    File.cpp
    Page.cpp
    SerializationUtils.cpp
    CompressionUtils.cpp
)

target_link_libraries(
    file_format PRIVATE 
    ${LZ4_LIB})

target_include_directories(
    file_format PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

