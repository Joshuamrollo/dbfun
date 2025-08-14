#include "klikedb/core/query_scheduler/QueryScheduler.h"
#include "klikedb/common/PhysicalOperator.h"
#include "klikedb/core/execution_engine/ExecutionEngine.h"

namespace klikedb {

QueryScheduler::QueryScheduler(ExecutionEngine& exec_eng) : _exec_engine(exec_eng) {}

void QueryScheduler::scheduleQuery(std::unique_ptr<LogicalOperator>& logical_plan_head, 
                       QueryResult& query_result) 
{
    std::unique_ptr<PhysicalOperator> physical_plan_head = 
        generatePhysicalPlan(logical_plan_head);
    
    _exec_engine.executePlan(physical_plan_head, query_result);
}

std::unique_ptr<PhysicalOperator> QueryScheduler::generatePhysicalPlan(
    std::unique_ptr<LogicalOperator>& logical_operator) 
{
    switch (logical_operator->_type) {
        case LogicalOperatorType::LOGICAL_GET: {
            
        }

        case LogicalOperatorType::LOGICAL_PROJECTION: {
            
        }

        case LogicalOperatorType::LOGICAL_INSERT: {
            
        }

        case LogicalOperatorType::LOGICAL_CREATE: {
            
        }

        default:
            throw std::runtime_error("Unsupported logical operator type in generatePhysicalPlan");
    }
}

}