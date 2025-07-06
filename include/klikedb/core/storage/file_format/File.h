#ifndef FILE_H
#define FILE_H

#include "klikedb/core/storage/file_format/Page.h"
#include <cstdint>
#include <string>
#include <unordered_map>

namespace klikedb {

constexpr std::size_t MAX_FILE_SIZE = 512 * 1024 * 1024; // 512mb

class FileMetadata {
public:
    std::uint32_t page_count;
    // using std::uint64_t bc off_t's width depends on system
    std::unordered_map<std::uint32_t, std::pair<std::uint64_t, std::uint64_t>> page_directory;

    FileMetadata();
    void addPage(std::uint32_t page_id, std::uint64_t page_offset);
    std::uint64_t getPageOffset(std::uint32_t page_id);
    bool doesPageIdExist(std::uint32_t page_id);
};

class File {
public: 
    File(const std::string& file_path);
    ~File();
    void openFileIfNeeded();
    Page readPage(std::uint32_t page_id); 
    std::uint32_t writePage(Page& page); 
    void closeFile();
    void writeFileMetadata();

private:
    FileMetadata _file_metadata;
    std::string _file_path;
    std::uint32_t _next_page_id;
    int _file_descriptor;
    bool _page_written;
};

}

#endif
