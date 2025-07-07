#include "klikedb/core/storage/io_manager/IOManager.h"
#include "klikedb/core/storage/file_format/File.h"

namespace klikedb {

IOManager::IOManager() {}

klikedb::File& IOManager::getFile(const std::string& file_path, bool write_mode) {
    //check if in open files
    auto itr = _open_files.find(file_path);
    if (itr != _open_files.end()) {
        if(!itr->second._write_mode) {
            itr->second._write_mode = write_mode;
            return *(itr->second._file_ptr);
        } else {
            // handle conflicts. ill work on this l8r when not single threaded :p
        }
    }

    // create new entry
    std::unique_ptr<File> new_file = std::make_unique<File>(file_path);
    File& file_ref = *new_file;  
    _open_files[file_path]._file_ptr = std::move(new_file);
    _open_files[file_path]._write_mode = write_mode;
    return file_ref;
}

void IOManager::doneWriting(const std::string& file_path) {
    auto itr = _open_files.find(file_path);
    if(itr != _open_files.end()) {
        itr->second._write_mode = false;
    }
}

void IOManager::createFile(const std::string& file_path) {
    File file(file_path);
}

void IOManager::closeFile(const std::string& file_path) {
    auto itr = _open_files.find(file_path);
    if(itr != _open_files.end()) {
        itr->second._file_ptr->closeFile();
        _open_files.erase(file_path);
    }
}

}