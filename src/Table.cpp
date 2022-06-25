#include <sstream>

#include "Table.h"

using namespace MySmallDb;

void Table::insert(std::map<std::string, std::string> &columnValue) {
    //TODO: impl
}


std::string Table::getTableName() const {
    return this->name;
}

std::vector<ColumnDefinition> Table::getColumnDefinitions() const {
    return this->columnDefinitions;
}

std::string Table::toString() const {
    std::stringstream output;
    output << "===============" << std::endl;
    output << "Table: " << this->getTableName() << std::endl;
    output << "===============" << std::endl;

    if (this->columnDefinitions.empty()) {
        output << "No columns defined ";
    } else {
        for (const auto &item: this->getColumnDefinitions()) {
            output << item.toString() << std::endl;
        }
    }

    return output.str();
}


Table Table::load(const std::string &dbName, const std::string &tableName) {
    const std::vector<ColumnDefinition> &columnDefs = ColumnDefinition::load(dbName, tableName);
    return {tableName, columnDefs};
}