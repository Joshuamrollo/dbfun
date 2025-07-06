// #include <algorithm>
#include <cassert>
#include <iostream>
#include "klikedb/core/storage/file_format/Page.h"
#include "klikedb/core/storage/file_format/SerializationUtils.h"
#include "klikedb/core/storage/file_format/CompressionUtils.h"
#include "klikedb/core/storage/file_format/File.h"

using namespace klikedb;

void testPageSerialization() {
    Page original(1, DataType::INT32);
    std::vector<uint8_t> dummy_data = {10, 20, 30, 40};
    original.setData(dummy_data);

    std::vector<uint8_t> serialized = SerializationUtils::serializePage(original);
    Page deserialized = SerializationUtils::deserializePage(serialized);

    assert(original.getPageId() == deserialized.getPageId());
    assert(original.getDataType() == deserialized.getDataType());
    assert(original.getData() == deserialized.getData());

    std::cout << "[PASS] Page serialization test\n";
}

void testCompression() {
    std::vector<uint8_t> big_repeating(4096, 'Z');
    // std::vector<uint8_t> big_random(4096);
    // std::generate(big_random.begin(), big_random.end(), std::rand);
    // std::vector<uint8_t> input = {1, 2, 3, 4, 5, 6, 7};
    std::vector<uint8_t> compressed = CompressionUtils::compressWithLZ4(big_repeating);
    std::cout << "compressed size: " << compressed.size() << "\n";
    std::vector<uint8_t> decompressed = CompressionUtils::decompressWithLZ4(compressed);
    std::cout << "decompressed size: " << decompressed.size() << "\n";

    assert(decompressed == input);
    std::cout << "[PASS] Compression round-trip test\n";
}

void testFileWriteRead() {
    File file("test_data/testfile.data");

    Page page(0, DataType::INT32);
    page.setData({1, 2, 3, 4});
    std::uint32_t id = file.writePage(page);

    Page read_back = file.readPage(id);

    assert(read_back.getPageId() == id);
    assert(read_back.getData() == page.getData());
    assert(read_back.getDataType() == page.getDataType());

    std::cout << "[PASS] File write-read test\n";

    file.closeFile();
}

int main() {
    testPageSerialization();
    testCompression();
    testFileWriteRead();

    std::cout << "bazinga all tests passed\n";
    return 0;
}
