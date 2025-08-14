#include "klikedb/core/catalog/Catalog.h"

namespace klikedb {

/*
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
*/

bool Catalog::tableExists(std::string table_name) {
    return true;
}

bool Catalog::columnsExists(std::string table_name, std::string column_name) {
    return true;
}

void Catalog::createTable(const std::string& name, const std::vector<Column>& columns) {
    
}

// const Table& Catalog::getTable(const std::string& name) const {
    
// }

// std::vector<std::string> Catalog::getColumnFilePaths(
//     const std::string& table_name,
//     const std::string& column_name) const
// {
    
// }

}
