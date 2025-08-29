#ifndef IO_MANAGER_H
#define IO_MANAGER_H
// todo rename to file manager just makejs more sense imo
#include "klikedb/common/DataType.h"
#include "klikedb/core/file_format/File.h"
#include <memory>

namespace klikedb {

class IOManager {
public:
    IOManager();
    File& getFile(const std::string& file_path, bool write_mode);
    void closeFile(const std::string& file_path); 
    void createFile(const std::string& file_path);
    void doneWriting(const std::string& file_path);
    std::unique_ptr<Page> getPage(const std::string& file_path, PageId page_id, bool write_mode);
    void writePage(std::string& file_path, Page& page);

private:
    struct FileEntry {
        std::unique_ptr<File> _file_ptr;
        bool _write_mode;
    };

    std::unordered_map<std::string, FileEntry> _open_files;
};

}

#endif
