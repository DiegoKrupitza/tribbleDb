
#include "ColumnConstraintValidators.h"

using namespace MySmallDb;

bool NonNullColumnConstraintValidator::validate(const Table &table, const ColumnDefinition &columnDefinition,
                                                const std::map<std::string, std::string> &columnValues) {
    return !(columnValues.find(columnDefinition.name) == columnValues.cend());
}

bool PositiveNumberColumnConstraintValidator::validate(const Table &table, const ColumnDefinition &columnDefinition,
                                                       const std::map<std::string, std::string> &columnValues) {

    const auto &fieldVal = columnValues.find(
            columnDefinition.name)->second;

    long pkValue = strtol(fieldVal.c_str(), nullptr, 10);
    return pkValue >= 0;
}

bool UniqueColumnConstraintValidator::validate(const Table &table, const ColumnDefinition &columnDefinition,
                                               const std::map<std::string, std::string> &columnValues) {
    return false;
}
