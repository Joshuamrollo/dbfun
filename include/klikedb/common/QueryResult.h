#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <string>
#include <vector>
namespace klikedb {

struct QueryResult {
    enum class ResultType { SELECT_RESULT, MESSAGE, ERROR };

    ResultType _type;
    std::vector<std::string> _column_names;
    std::vector<std::vector<std::string>> _rows;
    std::string _message;
    std::string _error_msg;

    void SetSelectResult(std::vector<std::string> column_names, 
        std::vector<std::vector<std::string>> rows);
    void SetMessage(const std::string& message);
    void SetError(const std::string& error_msg);
};

}

#endif 