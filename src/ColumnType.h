#ifndef MYSMALLDB_COLUMNTYPE_H
#define MYSMALLDB_COLUMNTYPE_H

#include <string>
#include <unordered_map>
#include <exception>

namespace MySmallDb {


    enum ColumnType {
        INT = 0,
        TEXT,
        CHAR
    };

    struct ColumnTypeHelper {

        static inline std::unordered_map<std::string, ColumnType> const table = {{"I", ColumnType::INT},
                                                                                 {"T", ColumnType::TEXT},
                                                                                 {"C", ColumnType::CHAR}};

        [[nodiscard]] static ColumnType from(const std::string &name) {
            return ColumnTypeHelper::table.find(name)->second;
        }

        [[nodiscard]] static std::string toString(const ColumnType &columnType) {
            switch (columnType) {
                case INT:
                    return "I";
                case TEXT:
                    return "T";
                case CHAR:
                    return "C";
            }
            throw std::invalid_argument("Cant convert the provided ColumnType to string");
        }
    };
}


#endif //MYSMALLDB_COLUMNTYPE_H
