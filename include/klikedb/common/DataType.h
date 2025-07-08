#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <cstdint>

namespace klikedb {

enum class DataType : std::uint8_t {
    INT32 = 0,
    INT64 = 1,
    // add more data types: timestamp, string, etc
};

// other types
using PageId = std::uint32_t;

}

#endif
