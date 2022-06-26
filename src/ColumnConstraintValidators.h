
#ifndef MYSMALLDB_COLUMNCONSTRAINTVALIDATORS_H
#define MYSMALLDB_COLUMNCONSTRAINTVALIDATORS_H

#include <string>
#include <vector>
#include "Table.h"

namespace MySmallDb {
    class ColumnConstraintValidator {
    public:
        ColumnConstraintValidator() = default;

        /**
         * Check whether the given value satisfies the constraint or not.
         * @param value the value to check
         * @return true - when the value satisfies otherwise false
         */
        [[nodiscard]] virtual bool validate(const Table &table, const ColumnDefinition &columnDefinition,
                                            const std::map<std::string, std::string> &columnValues) { return false; };
    };

    class NonNullColumnConstraintValidator : public ColumnConstraintValidator {
    public:

        NonNullColumnConstraintValidator() = default;

        bool validate(const Table &table, const ColumnDefinition &columnDefinition,
                      const std::map<std::string, std::string> &columnValues) override;

    };

    class PositiveNumberColumnConstraintValidator : public ColumnConstraintValidator {
    public:

        PositiveNumberColumnConstraintValidator() = default;

        bool validate(const Table &table, const ColumnDefinition &columnDefinition,
                      const std::map<std::string, std::string> &columnValues) override;
    };

    class UniqueColumnConstraintValidator : public ColumnConstraintValidator {
    public:

        UniqueColumnConstraintValidator() = default;

        bool validate(const Table &table, const ColumnDefinition &columnDefinition,
                      const std::map<std::string, std::string> &columnValues) override;

    };

    struct ColumnConstraintValidatorFactory {
        static ColumnConstraintValidator *get(const ColumnConstraint &columnConstraint) {
            switch (columnConstraint) {
                case NON_NULL: {
                    return new NonNullColumnConstraintValidator();
                }
                case POSITIVE_NUMBER:
                    return new PositiveNumberColumnConstraintValidator();
                case UNIQUE:
                    return new UniqueColumnConstraintValidator();
            }
            throw std::invalid_argument(
                    "No validator for the provided type: " + ColumnConstraintHelper::toString(columnConstraint));
        }
    };
}

#endif //MYSMALLDB_COLUMNCONSTRAINTVALIDATORS_H
