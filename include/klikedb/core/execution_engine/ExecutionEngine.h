#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H

#include "klikedb/core/buffer_manager/BufferManager.h"

namespace klikedb {

class ExecutionEngine {
public:
    ExecutionEngine(BufferManager& bufferManager);

    
private:
    BufferManager& _bufferManager;

};

}

#endif