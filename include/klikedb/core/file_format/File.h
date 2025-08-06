#ifndef FILE_H
#define FILE_H

#include "klikedb/core/file_format/Page.h"
#include <cstdint>
#include <string>
#include <unordered_map>

namespace klikedb {

constexpr std::size_t MAX_FILE_SIZE = 512 * 1024 * 1024; // 512mb

class FileMetadata {
public:
    std::uint32_t _page_count;
    // using std::uint64_t bc off_t's width depends on system
    std::unordered_map<PageId, std::pair<std::uint64_t, std::uint64_t>> _page_directory;

    FileMetadata();
    void addPage(PageId page_id, std::uint64_t page_offset);
    std::uint64_t getPageOffset(PageId page_id);
};

class File {
public: 
    File(const std::string& file_path);
    ~File();
    void openFileIfNeeded();
    Page readPage(PageId page_id); 
    PageId writePage(Page& page); 
    void closeFile();
    void writeFileMetadata();

private:
    FileMetadata _file_metadata;
    std::string _file_path;
    PageId _next_page_id;
    int _file_descriptor;
    bool _page_written;
};

}

#endif
