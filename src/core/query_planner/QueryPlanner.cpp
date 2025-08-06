#include "klikedb/core/query_planner/QueryPlanner.h"
#include "klikedb/common/LogicalOperator.h"
#include "src/sql/CreateStatement.h"
#include "src/sql/InsertStatement.h"
#include "src/sql/SelectStatement.h"
#include <memory>
#include <string>

namespace klikedb {

QueryPlanner::QueryPlanner(
    QueryScheduler& scheduler, Binder& binder, Rewriter& rewriter, 
    Optimizer& optimizer) : _binder(binder), _optimizer(optimizer), 
    _rewriter(rewriter), _scheduler(scheduler) {
    
}

void QueryPlanner::planQuery(std::unique_ptr<hsql::SQLStatement> statement, 
                             QueryResult& query_result) {
    
    if(_binder.isStatementValid(statement, query_result)) {
        std::unique_ptr<LogicalOperator> logical_plan_head = createLogicalPlan(statement);
        _rewriter.rewrite(logical_plan_head);
        _optimizer.optimize(logical_plan_head);
        _scheduler.scheduleQuery(logical_plan_head, query_result);
    } else {
        return;
    }
}

std::unique_ptr<LogicalOperator> QueryPlanner::createLogicalPlan(
    std::unique_ptr<hsql::SQLStatement>& statement) {
    switch (statement->type()) {
        case hsql::StatementType::kStmtSelect: {
            auto* select_stmt = 
                dynamic_cast<hsql::SelectStatement*>(statement.get());

            std::string table_name = select_stmt->fromTable->getName();

            std::vector<std::string> column_names;
            for (auto* expr : *select_stmt->selectList) {
                if (expr->type == hsql::ExprType::kExprColumnRef) {
                    column_names.emplace_back(expr->name);
                } else {
                    throw std::runtime_error(
                        "only supporting simple column expressions for now");
                }
            }

            auto get = std::make_unique<LogicalGet>(table_name);

            auto proj = std::make_unique<LogicalProjection>(column_names);
            proj->children.push_back(std::move(get));

            return proj;
        }

        case hsql::StatementType::kStmtInsert: {
            auto* insert_stmt = 
                dynamic_cast<hsql::InsertStatement*>(statement.get());

            std::string table_name = insert_stmt->tableName;

            std::vector<std::string> columns;
            if (insert_stmt->columns != nullptr) {
                for (auto* col : *insert_stmt->columns) {
                    columns.emplace_back(col);
                }
            }

            std::vector<std::vector<std::string>> values;
            size_t num_columns = columns.size();
            size_t total_values = insert_stmt->values->size();
            if (total_values % num_columns != 0) {
                throw std::runtime_error("INSERT statement has mismatched number of values");
            }

            for (size_t i = 0; i < total_values; i += num_columns) {
                std::vector<std::string> row;
                for (size_t j = 0; j < num_columns; ++j) {
                    hsql::Expr* expr = (*insert_stmt->values)[i + j];
                    if (expr->type == hsql::kExprLiteralString) {
                        row.emplace_back(expr->name);
                    } else if (expr->type == hsql::kExprLiteralInt) {
                        row.emplace_back(std::to_string(expr->ival));
                    } else if (expr->type == hsql::kExprLiteralFloat) {
                        row.emplace_back(std::to_string(expr->fval));
                    } else {
                        row.emplace_back("UNSUPPORTED_EXPR");
                    }
                }
                values.emplace_back(std::move(row));
            }

            return std::make_unique<LogicalInsert>(table_name, columns, values);
        }

        case hsql::StatementType::kStmtCreate: {
            auto* create_stmt = 
                dynamic_cast<hsql::CreateStatement*>(statement.get());

            std::string table_name = create_stmt->tableName;
            std::vector<std::pair<std::string, std::string>> columns;

            for (auto* col_def : *create_stmt->columns) {
                columns.emplace_back(col_def->name, 
                                   std::to_string(static_cast<int>(col_def->type.data_type)));
            }

            return std::make_unique<LogicalCreate>(table_name, columns);
        }

        default:
            throw std::runtime_error("Unsupported SQL statement type in planner.");
    }
};

}