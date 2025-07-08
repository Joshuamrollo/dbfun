#ifndef KLIKEDB_COMPRESSION_UTILS_H
#define KLIKEDB_COMPRESSION_UTILS_H

#include <vector>
#include <cstdint>
#include <lz4.h>

namespace klikedb {

class CompressionUtils {
public:
    static std::vector<uint8_t> compressWithLZ4(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decompressWithLZ4(const std::vector<uint8_t>& buffer);
};

} 

#endif
