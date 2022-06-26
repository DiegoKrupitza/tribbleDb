#include <sstream>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <fstream>

#include "ColumnTypeValidator.h"
#include "Table.h"
#include "FileUtils.h"
#include "ColumnConstraintValidators.h"

using namespace MySmallDb;

void Table::insert(const std::map<std::string, std::string> &columnValue) {

    std::vector<ColumnConstraint> violatedConstraints;

    std::stringstream row;

    for (const auto &item: this->columnDefinitions) {

        const auto fieldValue =
                columnValue.find(item.name) != columnValue.cend() ? columnValue.find(item.name)->second : "";

        bool validValue = ColumnTypeValidatorFactory::get(item.type)->validateValue(fieldValue);

        if (!validValue) {
            throw std::runtime_error("The column " + item.name + " cannot stored the value: " + fieldValue);
        }

        // check if constraints satisfied
        for (const auto &constraint: item.constraints) {
            ColumnConstraintValidator *pValidator = ColumnConstraintValidatorFactory::get(constraint);
            bool constraintSatisfied = pValidator->validate(*this, item, columnValue);

            if (!constraintSatisfied) {
                violatedConstraints.push_back(constraint);
            }

            delete pValidator;
        }

        row << fieldValue << ";";
    }

    if (!violatedConstraints.empty()) {
        throw std::runtime_error("You did not satisfy " + std::to_string(violatedConstraints.size()) + " constraints");
    }

    // remove the last ';'
    const auto &finalisedRow = row.str().substr(0, row.str().length() - 1);
    std::cout << finalisedRow << std::endl;

    // extract pk for hashing etc
    const ColumnDefinition &pk = this->getPrimaryKey();
    long pkValue = strtol(columnValue.find(pk.name)->second.c_str(), nullptr, 10);

    // find the correct bucket
    int fileSuffix = HashingStrategyHelper::hash(this->hashingStrategy, pkValue);
    const auto &dataPathString = FileUtils::tableDataLocation(this->dbName, this->name, fileSuffix);

    // write row to correct bucket
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