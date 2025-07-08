#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "klikedb/common/DataType.h"
#include "klikedb/core/file_format/Page.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace klikedb {

struct Frame {
    Page _page;
    bool _dirty;
    int _pin_count;
    bool _reference_bit;

    Frame(const Page& page);
};

class BufferManager {
public:
    std::unique_ptr<Page> fetchPage(PageId page_id);
    void unpinPage(PageId page_id);
    void markDirty(PageId page_id);
    void flushAll();

private:
    std::unique_ptr<Frame> evictFrame();
    void loadPageFromDisk(PageId page_id);
    void writePageToDisk(PageId page_id);

    std::unordered_map<PageId, std::unique_ptr<Frame>> _page_table;
    std::vector<Frame> _buffer_pool;
};

}

#endif