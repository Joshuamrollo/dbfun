#ifndef QUERY_SCHEDULER_H
#define QUERY_SCHEDULER_H

#include "klikedb/common/QueryResult.h"
#include "klikedb/core/execution_engine/ExecutionEngine.h"
#include "klikedb/common/LogicalOperator.h"
#include "klikedb/common/PhysicalOperator.h"
#include <memory>

namespace klikedb {

class QueryScheduler {
public:
    QueryScheduler(ExecutionEngine& exec_engine);

    void scheduleQuery(std::unique_ptr<LogicalOperator>& logical_plan_head, 
                       QueryResult& query_result);
private:
    std::unique_ptr<PhysicalOperator> generatePhysicalPlan(
        std::unique_ptr<LogicalOperator>& logical_operator);

    ExecutionEngine _exec_engine;

};

}

#endif