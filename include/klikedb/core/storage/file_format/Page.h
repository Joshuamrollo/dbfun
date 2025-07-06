#ifndef PAGE_H
#define PAGE_H

#include <cstdint>
#include <vector>
#include "klikedb/common/DataType.h"

namespace klikedb {

constexpr std::size_t PAGE_SIZE = 4096;

class Page {
public:
    Page(std::uint32_t id, DataType type);
    DataType getDataType() const;
    std::uint32_t getPageId() const;
    const std::vector<std::uint8_t>& getData() const;
    void setData(const std::vector<std::uint8_t>& data);

private:
    std::uint32_t _page_id;
    DataType _data_type;
    std::vector<std::uint8_t> _data; 
};

}

#endif
