#include "klikedb/core/storage/file_format/CompressionUtils.h"
#include <cstring>
#include <lz4.h>
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace klikedb {

std::vector<uint8_t> CompressionUtils::compressWithLZ4(const std::vector<uint8_t>& input) {
    /*
        lz4 requires output buffer memory allocated before compression bc worst case it can
        grow the size of the data. here we are calcing the worst case compression size + 4 
        bytes for header then allocating that memory :)
    */
    int maxCompressedSize = LZ4_compressBound(input.size());
    std::vector<uint8_t> output(sizeof(uint32_t) + maxCompressedSize);

    // writing header(original size of data) to the first 4 bytes of output
    std::uint32_t originalSize = input.size();
    std::memcpy(output.data(), &originalSize, sizeof(std::uint32_t));

    // lz4 compressing this data mad impressive style
    int compressedSize = LZ4_compress_default(
        reinterpret_cast<const char*>(input.data()),
        reinterpret_cast<char*>(output.data() + sizeof(std::uint32_t)),
        input.size(),
        maxCompressedSize
    );

    if (compressedSize <= 0) {
        throw std::runtime_error(
            "CompressionUtils::compressWithLZ4 error - lz4 compression failed");
    }

    // resize to actual compressed size
    output.resize(sizeof(std::uint32_t) + compressedSize);
    return output;
}

std::vector<uint8_t> CompressionUtils::decompressWithLZ4(const std::vector<uint8_t>& buffer) {
    if (buffer.size() < sizeof(std::uint32_t)) {
            throw std::runtime_error(
                "CompressionUtils::decompressWithLZ4 error - buffer too small");
        }

    std::uint32_t originalSize;
    std::memcpy(&originalSize, buffer.data(), sizeof(std::uint32_t));

    std::vector<std::uint8_t> output(originalSize);

    int decompressedBytes = LZ4_decompress_safe(
        reinterpret_cast<const char*>(buffer.data() + sizeof(std::uint32_t)),
        reinterpret_cast<char*>(output.data()),
        static_cast<int>(buffer.size() - sizeof(std::uint32_t)),
        static_cast<int>(originalSize)
    );

    if (decompressedBytes < 0) {
        throw std::runtime_error(
            "CompressionUtils::decompressWithLZ4 error - lz4 decompress failed");
    }

    return output;
}

}
