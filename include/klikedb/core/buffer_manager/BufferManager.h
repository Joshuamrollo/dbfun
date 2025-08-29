#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "klikedb/common/DataType.h"
#include "klikedb/core/file_format/Page.h"
#include "klikedb/core/io_manager/IOManager.h"
#include <unordered_map>
#include <vector>

namespace klikedb {

struct Frame {
    Page _page;
    bool _dirty;
    int _pin_count;
    bool _reference_bit;
    std::string _file_path;

    Frame(const Page& page, const std::string& file_path) : _page(page), _file_path(file_path) {
        _dirty = false;
        _pin_count = 1;
        _reference_bit = 1;
    }
};

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

}

#endif