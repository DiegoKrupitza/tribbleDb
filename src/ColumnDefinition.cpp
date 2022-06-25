#include "ColumnDefinition.h"
#include "FileUtils.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace MySmallDb;

std::string ColumnDefinition::toString() const {
    // `name {PK_FLAG,TYPE}`
    const std::string pk_flag = this->pk ? "1" : "0";
    return this->name + " {" + pk_flag + "," + ColumnTypeHelper::toString(this->type) + "}";

}

std::vector<ColumnDefinition> ColumnDefinition::load(const std::string &dbName, const std::string &tableName) {
    std::vector<ColumnDefinition> returnVal;
    const auto path = FileUtils::columndefinitionLocation(dbName, tableName);

    std::ifstream f(path);

    // skip first line
    std::string hashMode;
    std::getline(f, hashMode);

    std::string row;
    while (std::getline(f, row)) {
        returnVal.push_back(ColumnDefinition::parse(row));
    }

    f.close();

    return returnVal;
}

ColumnDefinition ColumnDefinition::parse(std::string &content) {

    std::istringstream str(content);

    const std::string &fieldName = content.substr(0, content.find(' '));

    const std::string &constraintString = content.substr(content.find('{') + 1,
                                                         content.find('}') - content.find('{') - 1);
    const auto constraints = parseFieldConstraints(constraintString);

    // we have in total 2 constraints, make sure all were found!
    assert(constraints.size() == 2);

    const bool isPk = constraints[0] == "1";
    const ColumnType type = ColumnTypeHelper::from(constraints[1]);

    return {
            fieldName,
            isPk,
            type
    };
}

bool MySmallDb::tableDefinitionsContainsPrimaryKey(std::vector<ColumnDefinition> &definitions) {
    return std::any_of(definitions.begin(), definitions.end(), [](ColumnDefinition &c) { return c.pk; });
}

std::array<std::string, 2> MySmallDb::parseFieldConstraints(const std::string &content) {

    std::array<std::string, 2> returnVals;

    std::array<std::string, 2>::size_type arrayPosition = 0;

    std::string contentCopy = content;
    size_t pos;
    std::string token;


    while ((pos = contentCopy.find(',')) != std::string::npos) {
        token = contentCopy.substr(0, pos);
        returnVals[arrayPosition++] = token;
        contentCopy.erase(0, pos + 1);
    }
    returnVals[arrayPosition++] = contentCopy;

    return returnVals;
}

