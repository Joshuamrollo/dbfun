#include "klikedb/core/storage/file_format/File.h"
#include "klikedb/core/storage/file_format/SerializationUtils.h"
#include "klikedb/core/storage/file_format/CompressionUtils.h"
#include <cstdint>
#include <filesystem>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

namespace klikedb {

FileMetadata::FileMetadata() {
    page_count = 0;
}

void FileMetadata::addPage(std::uint32_t page_id, std::uint64_t page_offset) {
    if(page_directory.find(page_id) != page_directory.end()) {
        throw std::runtime_error("FileMetadata::addPage error. page_id alr exists: " + 
            std::to_string(page_id));
    }
    page_count++;
    page_directory[page_id].first = page_offset;
}

std::uint64_t FileMetadata::getPageOffset(std::uint32_t page_id) {
    auto itr = page_directory.find(page_id);
    if(itr == page_directory.end()) {
        throw std::runtime_error("FileMetadata::getPageOffset error. page_id doesnt exist: " + 
            std::to_string(page_id));
    }
    return itr->second.first;
}

File::File(const std::string& file_path) 
    : _file_descriptor(-1), _next_page_id(0), _file_path(file_path), _page_written(false), 
    _file_metadata() {
    if (!std::filesystem::exists(_file_path)) {
        std::filesystem::path dir_path(_file_path);
        std::filesystem::create_directories(dir_path.parent_path());
        
        int temp_file_descriptor = open(_file_path.c_str(), O_CREAT, 0644);
        if (temp_file_descriptor < 0) {
            throw std::runtime_error("File::File error. failed to create file: " + 
                _file_path);
        }

        close(temp_file_descriptor);
    }
}

File::~File() {
    if(_file_descriptor >= 0) closeFile();
}

void File::openFileIfNeeded() {
    if (_file_descriptor == -1) {
        _file_descriptor = open(_file_path.c_str(), O_RDWR | O_CREAT, 0644);
        if (_file_descriptor < 0) {
            throw std::runtime_error(
                "File::openFileIfNeeded error - couldnt open file: " + _file_path);
        }
    }
}

Page File::readPage(std::uint32_t page_id) {
    openFileIfNeeded();
    std::uint64_t offset = _file_metadata.getPageOffset(page_id);

    if (lseek(_file_descriptor, static_cast<off_t>(offset), SEEK_SET) == -1) {
        throw std::runtime_error("File::readPage error - lseek failed");
    }

    // creating buffer with size of compressed page
    std::uint64_t compressed_size = _file_metadata.page_directory[page_id].second;
    std::vector<std::uint8_t> buffer(compressed_size);

    ssize_t bytes_read = read(_file_descriptor, buffer.data(), buffer.size());
    if (bytes_read != static_cast<ssize_t>(compressed_size)) {
        throw std::runtime_error("File::readPage error - read failed");
    }

    return SerializationUtils::deserializePage(CompressionUtils::decompressWithLZ4(buffer));
}


std::uint32_t File::writePage(Page& page) {
    openFileIfNeeded();
    _page_written = true;

    std::vector<std::uint8_t> data = 
        CompressionUtils::compressWithLZ4(SerializationUtils::serializePage(page));

    // seeking end of file which is where page will start
    off_t offset = lseek(_file_descriptor, 0, SEEK_END);
    if (offset == -1) {
        throw std::runtime_error("File::writePage error - lseek couldnt find end of file");
    }

    // writing data
    ssize_t bytes_written = write(_file_descriptor, data.data(), data.size());
    if (bytes_written != static_cast<ssize_t>(data.size())) {
        throw std::runtime_error("File::writePage error - failed to write data");
    }

    // update metadata
    std::uint32_t page_id = _next_page_id++;
    _file_metadata.addPage(page_id, static_cast<std::uint64_t>(offset));
    _file_metadata.page_directory[page_id] = std::make_pair(
        static_cast<std::uint64_t>(offset), static_cast<std::uint64_t>(bytes_written));

    return page_id;
}


void File::writeFileMetadata() {
    // serialize -> compress -> write -> add pointer
    std::vector<std::uint8_t> serialized_metadata = 
        SerializationUtils::serializeFileMetadata(_file_metadata);
    
}

void File::closeFile() {
    // if file in write mode then write metadata as footer before closing
    if(_file_descriptor == -1) return;

    if(_page_written) {
        writeFileMetadata();
    }

    close(_file_descriptor);
    _file_descriptor = -1;
}

}
