#ifndef CATALOG_H
#define CATALOG_H

#include "klikedb/common/DataType.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace klikedb {

struct Column {
    std::string _name;
    DataType _type; 
    std::vector<std::string> _file_paths;
};

struct Table {
    std::string _name;
    std::unordered_map<std::string, Column> _columns;
};

class Catalog {
public:
    bool tableExists(std::string table_name);
    bool columnsExists(std::string table_name, std::string column_name);
    void createTable(const std::string& name, const std::vector<Column>& columns);
    const Table& getTable(const std::string& name) const;
    std::vector<std::string> getColumnFilePaths(const std::string& table_name, 
        const std::string& column_name) const;

private:
    std::unordered_map<std::string, Table> _tables;
};


}

#endif