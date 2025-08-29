#include "klikedb/core/buffer_manager/BufferManager.h"
#include "klikedb/core/file_format/File.h"
#include "klikedb/core/io_manager/IOManager.h"
#include <memory>

namespace klikedb {

/*
class BufferManager {
public:
    BufferManager(IOManager& io_manager, size_t pool_size);
    ~BufferManager();

    Page& fetchPage(PageId page_id, std::string& file_path); 
    void unpinPage(PageId page_id, bool is_dirty);
    void markDirty(PageId page_id);
    void flushAll();

private:
    Frame* evictFrame();
    Frame* loadPage(PageId page_id);
    void flushPage(Frame& frame);

    std::unordered_map<PageId, Frame*> _page_table;
    std::vector<Frame> _buffer_pool;
    IOManager& _io_manager;
    size_t _clock_hand;
    size_t _pool_size;
};
*/


BufferManager::BufferManager(IOManager& io_manager, size_t pool_size)
    : _io_manager(io_manager), _pool_size(pool_size) {}

BufferManager::~BufferManager() {
    flushAll();
}

Page& BufferManager::fetchPage(PageId page_id, std::string& file_path) {
    // if page not in pool put it in the pool then return page yep
    if(_page_table.find(page_id) == _page_table.end()) {
        std::unique_ptr<Page> page = _io_manager.getPage(file_path, page_id, true);
        if(sizeof(_buffer_pool) == _pool_size) evictFrame();
        _buffer_pool.emplace_back(*page, file_path);
        _page_table[page_id] = &_buffer_pool.back();
    }

    return _page_table[page_id]->_page;
}

void BufferManager::unpinPage(PageId page_id, bool is_dirty) {
    _page_table[page_id]->_pin_count--;
    if(is_dirty) markDirty(page_id);
}

void BufferManager::markDirty(PageId page_id) {
    _page_table[page_id]->_dirty = true;
}

void BufferManager::flushAll() {
    for(const auto& [page_id, frame] : _page_table) {
        flushPage(*frame);
    }
}

Frame* BufferManager::evictFrame() {
    Frame* f;
    while(true) {
        for(const auto& [page_id, frame] : _page_table) {
            if(frame->_reference_bit == 0) {
                f = frame;
                flushPage(*f);
            } else {
                frame->_reference_bit = 0;
            }
        }
    }

    return f;
}   

void BufferManager::flushPage(Frame& frame) {
    _io_manager.writePage(frame._file_path, frame._page);
}


}