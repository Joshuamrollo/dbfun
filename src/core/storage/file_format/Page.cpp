#include "klikedb/core/storage/file_format/Page.h"

namespace klikedb {

Page::Page(std::uint32_t page_id, DataType data_type) 
    : _page_id(page_id), _data_type(data_type), _data(PAGE_SIZE) {
    return;
}

DataType Page::getDataType() const {
    return _data_type;
}

std::uint32_t Page::getPageId() const {
    return _page_id;
}

const std::vector<std::uint8_t>& Page::getData() const {
    return _data;
}

void Page::setData(const std::vector<std::uint8_t>& data) {
    _data = data;
}

}
