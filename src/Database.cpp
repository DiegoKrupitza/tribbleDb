#include "Database.h"
#include "FileUtils.h"
#include "HashingStrat.h"

#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace MySmallDb;


Database Database::createEmpty(const std::string &dbName) {
    auto dbpath = MySmallDb::FileUtils::pathForDb(dbName);

    // check whether there is already an existing db
    if (MySmallDb::FileUtils::exists(dbpath)) {
        throw std::runtime_error("You cannot override an existing database instance! The db with then name " + dbName +
                                 " already exists!");
    }

    std::filesystem::create_directories(dbpath);
    
    return Database{dbName, dbpath, {}};
}

Database Database::load(const std::string &dbName) {
    auto dbpath = MySmallDb::FileUtils::pathForDb(dbName);

    // check whether there is already an existing db
    if (!MySmallDb::FileUtils::exists(dbpath)) {
        throw std::runtime_error("The db with then name " + dbName +
                                 " does not exist!");
    }

    std::map<std::string, Table> tables;

    // load tables
    for (const auto &dir: std::filesystem::directory_iterator(dbpath)) {
        if (!dir.is_directory()) {
            continue;
        }
        const std::string &tableName = dir.path().filename().string();

        tables.insert(
                std::make_pair(tableName,
                               Table::load(dbName, tableName)
                )
        );
    }

    return Database{dbName, dbpath, tables};
}

Table Database::createTable(const std::string &tableName, std::vector<ColumnDefinition> &columnDefinitions,
                            HashingStrategy hashingStrategy) {

    std::cout << "Creating table: " << tableName << std::endl;

    if (!tableDefinitionsContainsPrimaryKey(columnDefinitions)) {
        throw std::runtime_error("Your table has to have a primary key!");
    }

    const std::string tableDefinitionLocation = MySmallDb::FileUtils::columndefinitionLocation(this->name, tableName);

    if (MySmallDb::FileUtils::exists(tableDefinitionLocation)) {
        throw std::runtime_error("The table with then name " + tableName + " already exists!");
    }

    // create parents
    std::filesystem::path tableDefpath{tableDefinitionLocation};
    std::filesystem::create_directories(tableDefpath.parent_path());

    std::cout << "ColumnDef Location: " << tableDefinitionLocation << std::endl;

    std::ofstream f(tableDefinitionLocation);

    // hashing mode
    f << hashingStrategy << std::endl;

    // column definitions
    for (const auto &item: columnDefinitions) {
        f << item.toString() << std::endl;
    }

    f.close();

    return {tableName, columnDefinitions};
}

void Database::deleteDb() {
    std::filesystem::remove_all(this->path);
}

Table &Database::getTable(const std::string &tableName) {
    return this->tables.find(tableName)->second;
}
