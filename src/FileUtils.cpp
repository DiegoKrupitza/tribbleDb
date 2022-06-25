#include <string>
#include <filesystem>
#include "FileUtils.h"

using namespace MySmallDb;

std::string FileUtils::dbBaseDir() {
    std::string homeDir(getenv("HOME"));
    return homeDir + separator() + "mysmalldb";
}

std::string FileUtils::pathForDb(const std::string &dbname) {
    return dbBaseDir() + separator() + dbname + ".db";
}

bool FileUtils::exists(const std::string &path) {
    return std::filesystem::exists(path);
}

std::string FileUtils::tablePath(const std::string &dbname, const std::string &tableName) {
    return pathForDb(dbname) + separator() + tableName;
}

std::string FileUtils::columndefinitionLocation(const std::string &dbname, const std::string &tableName) {
    return tablePath(dbname, tableName) + separator() + "table.def";
}
