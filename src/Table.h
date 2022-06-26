#ifndef MYSMALLDB_TABLE_H
#define MYSMALLDB_TABLE_H

#include <map>
#include <string>
#include <exception>

#include "ColumnDefinition.h"
#include "HashingStrat.h"

namespace MySmallDb {

    class Table {

    private:
        const std::string dbName;
        const std::string name;
        std::vector<ColumnDefinition> columnDefinitions;
        HashingStrategy hashingStrategy;

    public:

        Table(const std::string &dbName, const std::string &name,
              const std::vector<ColumnDefinition> &columnDefinitions,
              const HashingStrategy hashingStrategy) : dbName(dbName),
                                                       name(name),
                                                       columnDefinitions(
                                                               columnDefinitions),
                                                       hashingStrategy(hashingStrategy) {
            if (name.empty()) {
                throw std::invalid_argument("Name of a table is not allowed to be empty!");
            }
        }

        void insert(const std::map<std::string, std::string> &columnValue);

        [[nodiscard]] std::string getTableName() const;

        [[nodiscard]] std::vector<ColumnDefinition> getColumnDefinitions() const;

        [[nodiscard]] std::string toString() const;

        [[nodiscard]] const ColumnDefinition &getPrimaryKey();

        static Table load(const std::string &dbName, const std::string &tableName);

    };
}


#endif //MYSMALLDB_TABLE_H
