#include "klikedb/core/execution_engine/ExecutionEngine.h"
#include <stdexcept>

namespace klikedb {

ExecutionEngine::ExecutionEngine(BufferManager& bufferManager)
    : _bufferManager(bufferManager) {}

void ExecutionEngine::executePlan(
    std::unique_ptr<PhysicalOperator>& physical_plan_head, 
    QueryResult& query_result)
{
    if (!physical_plan_head) {
        throw std::invalid_argument("ExecutionEngine::executePlan - physical_plan_head is null");
    }

    // todo
}

}
