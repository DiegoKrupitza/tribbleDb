#ifndef tribbleDb_HASHINGSTRAT_H
#define tribbleDb_HASHINGSTRAT_H

#include <string>
#include <unordered_map>
#include <cstdlib>

namespace tribbleDb {
    enum HashingStrategy {
        MODULO = 0
    };

    struct HashingStrategyHelper {

        static inline std::unordered_map<int, HashingStrategy> const table = {{0, HashingStrategy::MODULO}
        };

        [[nodiscard]] static HashingStrategy from(const std::string &value) {
            long longVal = std::strtol(value.c_str(), nullptr, 10);
            return from(longVal);
        }

        [[nodiscard]] static HashingStrategy from(int value) {
            return HashingStrategyHelper::table.find(value)->second;
        }

        [[nodiscard]] static int toString(const HashingStrategy &hashingStrategy) {
            switch (hashingStrategy) {
                case MODULO:
                    return 0;
            }
            throw std::invalid_argument("Cant convert the provided ColumnType to string");
        }

        static int hash(HashingStrategy hashingStrategy, int val);

        static HashingStrategy load(const std::string &dbName, const std::string &tableName);
    };

}
#endif //tribbleDb_HASHINGSTRAT_H
