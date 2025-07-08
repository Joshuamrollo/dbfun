#ifndef IO_MANAGER_H
#define IO_MANAGER_H
// todo rename to file manager just makejs more sense imo
#include "klikedb/core/file_format/File.h"
#include <memory>

namespace klikedb {

class IOManager {
public:
    IOManager();
    klikedb::File& getFile(const std::string& file_path, bool write_mode);
    void closeFile(const std::string& file_path); 
    void createFile(const std::string& file_path);
    void doneWriting(const std::string& file_path);

private:
    struct FileEntry {
        std::unique_ptr<klikedb::File> _file_ptr;
        bool _write_mode;
    };

    std::unordered_map<std::string, FileEntry> _open_files;
};

}

#endif
