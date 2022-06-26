#ifndef TRIBBLEDB_DATABASE_H
#define TRIBBLEDB_DATABASE_H

#include <string>
#include <vector>
#include <map>

#include "ColumnDefinition.h"
#include "HashingStrat.h"
#include "Table.h"

namespace tribbleDb {

    class Database {

    private:
        const std::string name;
        const std::string path;

        std::map<std::string, Table> tables;

    public:
        Database(const std::string &dbName, const std::string &path, const std::map<std::string, Table> &tables) : name(
                dbName),
                                                                                                                   path(path),
                                                                                                                   tables(tables) {};

        Table createTable(const std::string &tableName, std::vector<ColumnDefinition> &columnDefinitions,
                          HashingStrategy strategy);

        Table createTable(const std::string &tableName, std::vector<ColumnDefinition> &columnDefinitions) {
            // default is modulo
            return Database::createTable(tableName, columnDefinitions, MODULO);
        };

        void deleteDb();

        static Database createEmpty(const std::string &dbName);

        static Database load(const std::string &dbName);

        [[nodiscard]] Table &getTable(const std::string &tableName);
    };

}

#endif //TRIBBLEDB_DATABASE_H
