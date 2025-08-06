#ifndef BINDER_H
#define BINDER_H

#include "klikedb/common/QueryResult.h"
#include "klikedb/core/catalog/Catalog.h"
#include "src/sql/Expr.h"
#include "src/sql/SQLStatement.h"
#include "src/sql/Table.h"

namespace klikedb {

class Binder {
public:
    Binder(Catalog& catalog);
    bool isStatementValid(const std::unique_ptr<hsql::SQLStatement>& statement, 
                          QueryResult& queryResult);

private:
    std::string statementTypeToString(hsql::StatementType type);
    bool validateTableRef(const hsql::TableRef* table_ref, QueryResult& query_result);
    bool validateTableName(const std::string& table_name, QueryResult& query_result);
    bool validateExpression(const hsql::Expr* expr, const hsql::TableRef* table_ref, 
                            QueryResult& query_result);
    bool validateColumn(const std::string& column_name, std::string& table_name, 
                        QueryResult& query_result);

    Catalog& _catalog;
    
};

}

#endif 