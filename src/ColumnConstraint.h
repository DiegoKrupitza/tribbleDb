#ifndef TRIBBLEDB_COLUMNCONSTRAINT_H
#define TRIBBLEDB_COLUMNCONSTRAINT_H

#include <string>
#include <exception>
#include <unordered_map>

namespace tribbleDb {


    enum ColumnConstraint {
        NON_NULL,
        POSITIVE_NUMBER,
        UNIQUE
    };

    struct ColumnConstraintHelper {

        [[nodiscard]] static ColumnConstraint from(const std::string &value) {
            return ColumnConstraintHelper::table.find(value)->second;
        }

        [[nodiscard]] static std::string toString(const ColumnConstraint &columnConstraint) {
            switch (columnConstraint) {
                case NON_NULL:
                    return "NonNull";
                case POSITIVE_NUMBER:
                    return "PositiveNumber";
                case UNIQUE:
                    return "Unique";
            }
            throw std::invalid_argument("Cant convert the provided ColumnConstraint to string");
        }

        static inline std::unordered_map<std::string, ColumnConstraint> const table = {
                {toString(NON_NULL),        NON_NULL},
                {toString(POSITIVE_NUMBER), POSITIVE_NUMBER},
                {toString(UNIQUE),          UNIQUE}
        };
    };

}


#endif //TRIBBLEDB_COLUMNCONSTRAINT_H
