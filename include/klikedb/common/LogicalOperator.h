#ifndef LOGICAL_OPERATOR_H
#define LOGICAL_OPERATOR_H

#include <memory>
#include <vector>

namespace klikedb {

enum class LogicalOperatorType {
    LOGICAL_GET,
    LOGICAL_PROJECTION,
    LOGICAL_INSERT,
    LOGICAL_CREATE,
};

class LogicalOperator {
public:
    LogicalOperatorType _type;
    std::vector<std::unique_ptr<LogicalOperator>> _children;

    explicit LogicalOperator(LogicalOperatorType type)
        : _type(type) {}

    virtual ~LogicalOperator() = default;
};

class LogicalGet : public LogicalOperator {
public:
    std::string _table_name;

    LogicalGet(const std::string& table_name)
        : LogicalOperator(LogicalOperatorType::LOGICAL_GET),
          _table_name(table_name) {}
};

class LogicalProjection : public LogicalOperator {
public:
    std::vector<std::string> _columns;

    LogicalProjection(std::vector<std::string> columns)
        : LogicalOperator(LogicalOperatorType::LOGICAL_PROJECTION),
          _columns(std::move(columns)) {}
};

class LogicalInsert : public LogicalOperator {
public:
    std::string _table_name;
    std::vector<std::string> _columns;
    std::vector<std::vector<std::string>> _values;

    LogicalInsert(
        std::string& table_name,
        std::vector<std::string> columns,
        std::vector<std::vector<std::string>> values)
        : LogicalOperator(LogicalOperatorType::LOGICAL_INSERT),
          _table_name(table_name),
          _columns(std::move(columns)),
          _values(std::move(values)) {}
};

class LogicalCreate : public LogicalOperator {
public:
    std::string _table_name;
    std::vector<std::pair<std::string, std::string>> _columns;

    LogicalCreate(
        const std::string& table_name,
        std::vector<std::pair<std::string, std::string>> columns)
        : LogicalOperator(LogicalOperatorType::LOGICAL_CREATE),
          _table_name(table_name),
          _columns(std::move(columns)) {}
};


}

#endif