#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H

#include "klikedb/common/PhysicalOperator.h"
#include "klikedb/common/QueryResult.h"
#include "klikedb/core/buffer_manager/BufferManager.h"

namespace klikedb {

class ExecutionEngine {
public:
    ExecutionEngine(BufferManager& bufferManager);

    void executePlan(std::unique_ptr<PhysicalOperator>& physical_plan_head, 
                     QueryResult& query_result);
private:
    BufferManager& _bufferManager;

};

}

#endif