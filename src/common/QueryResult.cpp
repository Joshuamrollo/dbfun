#include "klikedb/common/QueryResult.h"

namespace klikedb {

void QueryResult::SetSelectResult(std::vector<std::string> column_names, 
                             std::vector<std::vector<std::string>> rows) {
    _type = QueryResult::ResultType::SELECT_RESULT;
    _column_names = std::move(column_names);
    _rows = std::move(rows);
}

void QueryResult::SetMessage(const std::string& message) { 
    _type = QueryResult::ResultType::MESSAGE;
    _message = message;
}

void QueryResult::SetError(const std::string& error_msg) {
    _type = QueryResult::ResultType::ERROR;
    _error_msg = error_msg;
}

}