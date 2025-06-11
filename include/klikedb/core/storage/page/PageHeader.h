#ifndef PAGE_HEADER_H
#define PAGE_HEADER_H

#include <klikedb/common/DataType.h>

struct PageHeader {
    DataType data_type;       // 1 byte
    std::uint8_t reserved[3]; // 3 bytes padding
    std::uint32_t row_count;  // 4 bytes
    std::int64_t min_value;   // 8 bytes
    std::int64_t max_value;   // 8 bytes

    PageHeader();
    PageHeader(DataType, std::uint8_t, std::uint32_t);
    PageHeader(DataType, std::uint8_t, std::uint32_t, std::int64_t, std::int64_t);
}; 

#endif
