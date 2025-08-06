#include "klikedb/core/front_end/FrontEnd.h"
#include "klikedb/common/QueryResult.h"
#include "klikedb/core/query_planner/QueryPlanner.h"
#include "src/SQLParser.h"
#include "src/SQLParserResult.h"
#include "src/sql/SQLStatement.h"
#include <iostream>

namespace klikedb {

FrontEnd::FrontEnd(QueryPlanner& planner) : _planner(planner) {}

void FrontEnd::processQuery(std::string input) {
    // parse sql
    hsql::SQLParserResult result;
    hsql::SQLParser::parse(input, &result);
    QueryResult queryResult;

    // send to planner 
    if(result.isValid()) {
        // temporarily using releaseStatements so statements arent const when passing to planner
        std::vector<hsql::SQLStatement*> statements = result.releaseStatements();
        for(size_t i = 0; i < statements.size(); i++) {
            auto statement = std::unique_ptr<hsql::SQLStatement>(statements[i]);
            _planner.planQuery(std::move(statement), queryResult);
        }
    } else {
        std::string error_message = static_cast<std::string>("error parsing query: ") 
            + result.errorMsg();
        queryResult.SetError(error_message);
    }

    // output results to user
    switch (queryResult._type) {
        case QueryResult::ResultType::SELECT_RESULT:
            for (const auto& col : queryResult._column_names)
                std::cout << col << "\t";
            std::cout << "\n";

            for (const auto& row : queryResult._rows) {
                for (const auto& cell : row)
                    std::cout << cell << "\t";
                std::cout << "\n";
            }
            break;

        case QueryResult::ResultType::MESSAGE:
            std::cout << queryResult._message << "\n";
            break;

        case QueryResult::ResultType::ERROR:
            std::cerr << "Error: " << queryResult._error_msg << "\n";
            break;
    }
}

}