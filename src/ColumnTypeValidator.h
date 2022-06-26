#ifndef TRIBBLEDB_COLUMNTYPEVALIDATOR_H
#define TRIBBLEDB_COLUMNTYPEVALIDATOR_H

#include <string>
#include <algorithm>
#include <exception>
#include "ColumnType.h"

namespace tribbleDb {

    class ColumnTypeValidator {
    public:
        ColumnTypeValidator() = default;

        /**
         * Check whether the given value is a valid value for the given column type
         * @param value the value to check
         * @return true - when the value is valid otherwise false
         */
        [[nodiscard]] virtual bool validateValue(const std::string &value) { return false; };
    };

    class IntColumnTypeValidator : public ColumnTypeValidator {
    public:

        IntColumnTypeValidator() = default;

        bool validateValue(const std::string &value) override {
            bool onlyDigits = std::all_of(value.cbegin(), value.cend(), [](const auto &v) { return isdigit(v); });
            return onlyDigits;
        }
    };

    class TextColumnTypeValidator : public ColumnTypeValidator {
    public:

        TextColumnTypeValidator() = default;

        bool validateValue(const std::string &value) override {
            return true;
        }
    };

    class CharColumnTypeValidator : public ColumnTypeValidator {
    public:

        CharColumnTypeValidator() = default;

        bool validateValue(const std::string &value) override {
            return value.length() <= 1;
        }
    };

    struct ColumnTypeValidatorFactory {
        static ColumnTypeValidator *get(const ColumnType &columnType) {
            switch (columnType) {
                case INT: {
                    return new IntColumnTypeValidator();
                }
                case TEXT:
                    return new TextColumnTypeValidator();
                case CHAR:
                    return new CharColumnTypeValidator();
            }
            throw std::invalid_argument(
                    "No validator for the provided type: " + ColumnTypeHelper::toString(columnType));
        }
    };
}

#endif //TRIBBLEDB_COLUMNTYPEVALIDATOR_H
