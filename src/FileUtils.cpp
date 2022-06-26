#include <string>
#include <filesystem>

#include "FileUtils.h"

using namespace tribbleDb;

std::string FileUtils::dbBaseDir() {
    std::string homeDir(getenv("HOME"));
    return homeDir + separator() + "tribbleDb";
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

std::string FileUtils::tableDataLocation(const std::string &dbname, const std::string &tableName, int suffix) {
    return tablePath(dbname, tableName) + separator() + "tablecontent-bucket-" + std::to_string(suffix) + ".data";
}
