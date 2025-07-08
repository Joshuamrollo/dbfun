#ifndef KLIKEDB_SERIALIZATION_UTILS_H
#define KLIKEDB_SERIALIZATION_UTILS_H

#include <vector>
#include <cstdint>
#include "klikedb/core/file_format/Page.h"
#include "klikedb/core/file_format/File.h"

namespace klikedb {

class SerializationUtils {
public:
    static std::vector<std::uint8_t> serializePage(const Page& page);
    static Page deserializePage(const std::vector<uint8_t>& buffer);

    static std::vector<std::uint8_t> serializeFileMetadata(const FileMetadata& metadata);
    static FileMetadata deserializeFileMetadata(const std::vector<uint8_t>& buffer);
};

}

#endif 
