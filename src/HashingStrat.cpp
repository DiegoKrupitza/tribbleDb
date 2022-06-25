#include <fstream>

#include "HashingStrat.h"
#include "FileUtils.h"


using namespace MySmallDb;

int HashingStrategyHelper::hash(HashingStrategy hashingStrategy, int val) {
    //TODO: implement various hash modes
    return val % 5;
}

HashingStrategy HashingStrategyHelper::load(const std::string &dbName, const std::string &tableName) {
    const auto path = FileUtils::columndefinitionLocation(dbName, tableName);

    std::ifstream f(path);

    // skip first line
    std::string hashMode;
    std::getline(f, hashMode);

    return HashingStrategyHelper::from(hashMode);
}
