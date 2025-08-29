#include "klikedb/core/io_manager/IOManager.h"
#include "klikedb/core/file_format/File.h"
#include <memory>

namespace klikedb {

IOManager::IOManager() {}

File& IOManager::getFile(const std::string& file_path, bool write_mode) {
    //check if in open files
    auto itr = _open_files.find(file_path);
    if (itr != _open_files.end()) {
        return *(itr->second._file_ptr);
    }

    // create new entry
    std::unique_ptr<File> new_file = std::make_unique<File>(file_path);
    File& file_ref = *new_file;  
    _open_files[file_path]._file_ptr = std::move(new_file);
    _open_files[file_path]._write_mode = write_mode;
    return file_ref;
}

std::unique_ptr<Page> IOManager::getPage(const std::string& file_path, PageId page_id, bool write_mode) {
    File file = getFile(file_path, write_mode);
    std::unique_ptr<Page> page = std::make_unique<Page>(file.readPage(page_id));
    return page;
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

void IOManager::writePage(std::string& file_path, Page& page) {
    _open_files[file_path]._file_ptr->writePage(page);
}

}