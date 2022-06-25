#include <sstream>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <fstream>

#include "ColumnTypeValidator.h"
#include "Table.h"
#include "FileUtils.h"

using namespace MySmallDb;

int satisfiesPkConstraints(const std::map<std::string, std::string> &columnValue, const ColumnDefinition &pk) {
    if (columnValue.find(pk.name) == columnValue.cend()) {
        throw std::runtime_error("Could not find pk in insert statement!");
    }

    auto pkInsertField = columnValue.find(pk.name)->second;
    bool validPkType = ColumnTypeValidatorFactory::get(pk.type)->validateValue(pkInsertField);

    if (!validPkType) {
        throw std::runtime_error("PK has to be a number!");
    }

    long pkValue = strtol(pkInsertField.c_str(), nullptr, 10);
    if (pkValue < 0) {
        throw std::runtime_error("PK has to be a positive number!");
    }

    return pkValue;
}

void Table::insert(const std::map<std::string, std::string> &columnValue) {
    // pk is the only required field. The remaining fields can be "empty"
    const ColumnDefinition &pk = this->getPrimaryKey();

    const auto pkValue = satisfiesPkConstraints(columnValue, pk);

    std::stringstream row;

    for (const auto &item: this->columnDefinitions) {
        if (item.name == pk.name) {
            // no processing needed since pk is already processed above
            row << pkValue << ";";
        } else {
            const auto fieldValue =
                    columnValue.find(item.name) != columnValue.cend() ? columnValue.find(item.name)->second : "";

            bool validValue = ColumnTypeValidatorFactory::get(item.type)->validateValue(fieldValue);

            if (!validValue) {
                throw std::runtime_error("The column " + item.name + " cannot stored the value: " + fieldValue);
            }

            row << fieldValue << ";";
        }
    }

    const auto &finalisedRow = row.str().substr(0, row.str().length() - 1);
    std::cout << finalisedRow << std::endl;

    int fileSuffix = HashingStrategyHelper::hash(this->hashingStrategy, pkValue);
    const auto &dataPathString = FileUtils::tableDataLocation(this->dbName, this->name, fileSuffix);

    std::ofstream f(dataPathString, std::ios::app);

    f << finalisedRow << std::endl;

    f.close();
}

const ColumnDefinition &Table::getPrimaryKey() {

    const auto pkFindResult = std::find_if(this->columnDefinitions.cbegin(), this->columnDefinitions.cend(),
                                           [](const ColumnDefinition &arg) {
                                               return arg.pk;
                                           });

    if (pkFindResult == this->columnDefinitions.cend()) {
        throw std::runtime_error("Could not find the primary key of the table: " + this->name);
    }

    return *pkFindResult;
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
    HashingStrategy hashingStrategy = HashingStrategyHelper::load(dbName, tableName);
    return {dbName, tableName, columnDefs, hashingStrategy};
}