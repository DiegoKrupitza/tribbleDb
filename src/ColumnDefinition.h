#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <exception>
#include "ColumnType.h"
#include <array>

#ifndef MYSMALLDB_COLUMNDEFINITION_H
#define MYSMALLDB_COLUMNDEFINITION_H

namespace MySmallDb {

    struct ColumnDefinition {

        std::string name;
        bool pk;
        ColumnType type;

        ColumnDefinition(const std::string name, bool pk, ColumnType type) : name(name), pk(pk), type(type) {};

        [[nodiscard]] std::string toString() const;

        static std::vector<ColumnDefinition> load(const std::string &dbName, const std::string &tableName);

        static ColumnDefinition parse(std::string &content);
    };

    bool tableDefinitionsContainsPrimaryKey(std::vector<ColumnDefinition> &definitions);

    std::array<std::string, 2> parseFieldConstraints(const std::string &content);
}

#endif //MYSMALLDB_COLUMNDEFINITION_H
