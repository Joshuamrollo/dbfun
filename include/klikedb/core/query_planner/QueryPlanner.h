#ifndef QUERY_PLANNER_H
#define QUERY_PLANNER_H

#include "klikedb/common/LogicalOperator.h"
#include "klikedb/common/QueryResult.h"
#include "klikedb/core/query_planner/Binder.h"
#include "klikedb/core/query_planner/Rewriter.h"
#include "klikedb/core/query_planner/Optimizer.h"
#include "klikedb/core/query_scheduler/QueryScheduler.h"
#include "src/sql/SQLStatement.h"

namespace klikedb {

class QueryPlanner {
public:
    QueryPlanner(QueryScheduler& scheduler, Binder& binder, Rewriter& rewriter, 
                 Optimizer& optimizer);
    // receives SQL statements from frontend -> 
    // calls binder to validate these stmts using catalog ->
    // creates logical plan ->
    // rewriter rewrites query for easy optimizations using heuristics ->
    // optimizer runs cost estimates to try and predict optimized query execution order ->
    // passes it to scheduler
void planQuery(std::unique_ptr<hsql::SQLStatement> statement, QueryResult& query_result);

private:
    std::unique_ptr<LogicalOperator> createLogicalPlan(
        std::unique_ptr<hsql::SQLStatement>& statement);

    Binder& _binder;
    Rewriter& _rewriter;
    Optimizer& _optimizer;
    QueryScheduler& _scheduler;
};

}

#endif 