#include "klikedb/core/buffer_manager/BufferManager.h"
#include "klikedb/core/io_manager/IOManager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace klikedb {

/*
class BufferManager {
public:
    BufferManager(IOManager& io_manager, size_t pool_size);

    Page& fetchPage(PageId page_id); 
    void unpinPage(PageId page_id);
    void markDirty(PageId page_id);
    void flushAll();

private:
    Frame* evictFrame();
    Frame* loadPage(PageId page_id);
    void writePageToDisk(Frame& frame);

    std::unordered_map<PageId, Frame*> _page_table;
    std::vector<Frame> _buffer_pool;
    IOManager& _ioManager;
    size_t _clock_hand;
};
*/


BufferManager::BufferManager(IOManager& io_manager, size_t pool_size)
    : _io_manager(io_manager), _pool_size(pool_size) {}

BufferManager::~BufferManager() {
    flushAll();
}

}