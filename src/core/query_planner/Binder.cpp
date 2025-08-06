#include "klikedb/core/query_planner/Binder.h"
#include "klikedb/core/catalog/Catalog.h"
#include "src/sql/CreateStatement.h"
#include "src/sql/InsertStatement.h"
#include "src/sql/SQLStatement.h"
#include "src/sql/SelectStatement.h"
#include "src/sql/Table.h"

namespace klikedb {

Binder::Binder(Catalog& catalog) : _catalog(catalog) {}

// will break up this function later
bool Binder::isStatementValid(const std::unique_ptr<hsql::SQLStatement>& statement, 
                              QueryResult& query_result) {
    const hsql::SQLStatement* stmt = statement.get();

    if(stmt->type() == hsql::kStmtSelect) {
        auto* select = 
            dynamic_cast<const hsql::SelectStatement*>(stmt);
        if(!select) {
            query_result.SetError("failed casting to SelectStatement");
            return false;
        }
        // check table exists
        const hsql::TableRef* table_ref = select->fromTable;
        if(!validateTableRef(table_ref, query_result)) return false;

        // check columns
        for (const auto* expr : *select->selectList) {
            if(!validateExpression(expr, table_ref, query_result)) return false;
        }

        return true;
    } else if(stmt->type() == hsql::kStmtInsert) {
        auto* insert = 
            dynamic_cast<const hsql::InsertStatement*>(stmt);
        if(!insert) {
            query_result.SetError("failed casting to InsertStatement");
            return false;
        }
        // check table exists
        std::string table_name = insert->tableName;
        if(!validateTableName(table_name, query_result)) return false;

        // check columns
        for (const auto* column : *insert->columns) {
            if(!validateColumn(std::string(column), table_name, query_result)) return false;
        }

        return true;
    } else if(stmt->type() == hsql::kStmtCreate) {
        auto* create = 
            dynamic_cast<const hsql::CreateStatement*>(stmt);
        if(!create) {
            query_result.SetError("failed casting to CreateStatement");
            return false;
        }
        // check if already exists
        std::string table_name = create->tableName;
        if(validateTableName(table_name, query_result)) {
            query_result.SetError("table already exists: " + table_name);
            return false;
        }

        return true;
    } else {
        query_result.SetError("this DBMS doesnt support this SQL operator yet: " + 
                             statementTypeToString(stmt->type()));
        return false;
    }
}

bool Binder::validateTableRef(const hsql::TableRef* table_ref, QueryResult& query_result) {
    if (table_ref->type != hsql::kTableName) {
        query_result.SetError("only simple table names are supported atm");
        return false;
    }

    const std::string table_name = table_ref->name;
    if (!_catalog.tableExists(table_name)) {
        query_result.SetError("Table does not exist: " + table_name);
        return false;
    }

    return true;
}

bool Binder::validateTableName(const std::string& table_name, QueryResult& query_result) {
    if (!_catalog.tableExists(table_name)) {
        query_result.SetError("Table does not exist: " + table_name);
        return false;
    }

    return true;
}

bool Binder::validateExpression(const hsql::Expr* expr, const hsql::TableRef* table_ref, 
                          QueryResult& query_result) {
    if (expr->type == hsql::kExprStar) {
        return true;
    }

    if (expr->type != hsql::kExprColumnRef) {
        query_result.SetError(
                "Only column references are supported in SELECT clause");
        return false;
    }

    std::string col_name = expr->name;

    if (!_catalog.columnsExists(table_ref->name, col_name)) {
        query_result.SetError("Column does not exist: " + col_name + 
                        " in table " + table_ref->name);
        return false;
    }

    return true;
}

bool Binder::validateColumn(const std::string& column_name, std::string& table_name, 
                            QueryResult& query_result) {
    if (!_catalog.columnsExists(table_name, column_name)) {
        query_result.SetError("Column does not exist: " + column_name + 
                        " in table " + table_name);
        return false;
    }

    return true;
}

std::string Binder::statementTypeToString(hsql::StatementType type) {
    switch (type) {
        case hsql::kStmtSelect: return "SELECT";
        case hsql::kStmtInsert: return "INSERT";
        case hsql::kStmtUpdate: return "UPDATE";
        case hsql::kStmtDelete: return "DELETE";
        case hsql::kStmtCreate: return "CREATE";
        case hsql::kStmtDrop:   return "DROP";
        case hsql::kStmtPrepare: return "PREPARE";
        case hsql::kStmtExecute: return "EXECUTE";
        case hsql::kStmtImport:  return "IMPORT";
        case hsql::kStmtExport:  return "EXPORT";
        default: return "UNKNOWN";
    }
}

}