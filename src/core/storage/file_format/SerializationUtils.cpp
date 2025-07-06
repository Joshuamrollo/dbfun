#include "klikedb/core/storage/file_format/SerializationUtils.h"
#include "klikedb/core/storage/file_format/Page.h"
#include <cstring>

namespace klikedb {

std::vector<std::uint8_t> SerializationUtils::serializePage(const Page& page) {
    std::vector<std::uint8_t> buffer;

    // page id 
    std::uint32_t id = page.getPageId();
    buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&id), 
        reinterpret_cast<uint8_t*>(&id) + sizeof(id));

    // data type
    std::uint32_t type = static_cast<std::uint32_t>(page.getDataType());
    buffer.insert(buffer.end(), reinterpret_cast<uint8_t*>(&type), 
        reinterpret_cast<uint8_t*>(&type) + sizeof(type));

    // data
    const auto& data = page.getData(); 
    buffer.insert(buffer.end(), data.begin(), data.end());

    return buffer;
}

Page SerializationUtils::deserializePage(const std::vector<uint8_t>& buffer) {
    std::size_t offset = 0;

    // page_id
    std::uint32_t page_id;
    std::memcpy(&page_id, buffer.data() + offset, sizeof(page_id));
    offset += sizeof(page_id);

    // data_type
    std::uint32_t type_raw;
    std::memcpy(&type_raw, buffer.data() + offset, sizeof(type_raw));
    DataType type = static_cast<DataType>(type_raw);
    offset += sizeof(type_raw);

    // data
    std::vector<uint8_t> data(buffer.begin() + offset, buffer.end());

    Page page(page_id, type);
    page.setData(data);

    return page;
}

std::vector<std::uint8_t> SerializationUtils::serializeFileMetadata(const FileMetadata& metadata) {
    std::vector<std::uint8_t> buffer;

    // page coutn
    buffer.insert(buffer.end(),
                  reinterpret_cast<const uint8_t*>(&metadata.page_count),
                  reinterpret_cast<const uint8_t*>(&metadata.page_count) + 
                    sizeof(metadata.page_count));

    // directory size
    std::uint32_t dir_size = metadata.page_directory.size();
    buffer.insert(buffer.end(),
                  reinterpret_cast<const uint8_t*>(&dir_size),
                  reinterpret_cast<const uint8_t*>(&dir_size) + sizeof(dir_size));

    // page id + pair
    for (const auto& [page_id, pairOffSize] : metadata.page_directory) {
        const auto& [offset, size] = pairOffSize;
        buffer.insert(buffer.end(),
                  reinterpret_cast<const uint8_t*>(&page_id),
                  reinterpret_cast<const uint8_t*>(&page_id) + sizeof(page_id));

        buffer.insert(buffer.end(),
                    reinterpret_cast<const uint8_t*>(&offset),
                    reinterpret_cast<const uint8_t*>(&offset) + sizeof(offset));

        buffer.insert(buffer.end(),
                    reinterpret_cast<const uint8_t*>(&size),
                    reinterpret_cast<const uint8_t*>(&size) + sizeof(size));
    }

    return buffer;
}

FileMetadata SerializationUtils::deserializeFileMetadata(const std::vector<uint8_t>& buffer) {
    std::size_t offset = 0;
    FileMetadata metadata;

    // page_count
    std::memcpy(&metadata.page_count, buffer.data() + offset, 
        sizeof(metadata.page_count));
    offset += sizeof(metadata.page_count);

    // dir size
    std::uint32_t dir_size;
    std::memcpy(&dir_size, buffer.data() + offset, sizeof(dir_size));
    offset += sizeof(dir_size);

    // page id + pair
    for (std::uint32_t i = 0; i < dir_size; ++i) {
        std::uint32_t page_id;
        std::uint64_t offset, size;

        std::memcpy(&page_id, &buffer[offset], sizeof(page_id));
        offset += sizeof(page_id);

        std::memcpy(&offset, &buffer[offset], sizeof(offset));
        offset += sizeof(offset);

        std::memcpy(&size, &buffer[offset], sizeof(size));
        offset += sizeof(size);

        metadata.page_directory[page_id] = std::make_pair(offset, size);
    }

    return metadata;
}


}
