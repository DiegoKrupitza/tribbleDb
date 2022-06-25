#include <map>
#include <string>
#include <exception>

#include "ColumnDefinition.h"

#ifndef MYSMALLDB_TABLE_H
#define MYSMALLDB_TABLE_H

namespace MySmallDb {

    class Table {

    private:
        const std::string name;
        std::vector<ColumnDefinition> columnDefinitions;

    public:

        Table(const std::string &name, const std::vector<ColumnDefinition> &columnDefinitions) : name(name),
                                                                                                 columnDefinitions(
                                                                                                         columnDefinitions) {
            if (name.empty()) {
                throw std::invalid_argument("Name of a table is not allowed to be empty!");
            }
        }

        void insert(std::map<std::string, std::string> &columnValue);

        [[nodiscard]] std::string getTableName() const;

        [[nodiscard]] std::vector<ColumnDefinition> getColumnDefinitions() const;

        [[nodiscard]] std::string toString() const;


        static Table load(const std::string &dbName, const std::string &tableName);
    };
}


#endif //MYSMALLDB_TABLE_H
