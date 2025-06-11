#ifndef PAGE_H
#define PAGE_H

#include <limits>
#include <optional>
#include <klikedb/common/DataType.h>
#include <klikedb/core/storage/page/PageHeader.h>
#include <klikedb/core/storage/page/PageUtils.h>

constexpr std::size_t NUM_ROWS = 1024;
constexpr std::size_t BITMAP_BYTES = NUM_ROWS / 8; // 1024 / 8 = 128 

template<typename T>
class Page {
public:
    PageHeader header;
    std::uint8_t null_bitmap[BITMAP_BYTES]; 
    T data[NUM_ROWS]; 

    Page(DataType type) {
        header.data_type = type;
        header.row_count = 0;
        
        if (isMinMaxSupported(type)) {
            header.min_value = std::numeric_limits<std::int64_t>::max();
            header.max_value = std::numeric_limits<std::int64_t>::min();
        } else {
            header.min_value = 0; 
            header.max_value = 0; 
        }
    }

    void add(std::optional<T> value) {
        // todo
    }
};

#endif
