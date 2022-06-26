#ifndef TRIBBLEDB_FILEUTILS_H
#define TRIBBLEDB_FILEUTILS_H

#include <string>
#include <cstdlib>

namespace tribbleDb::FileUtils {


    inline char separator() {
#ifdef _WIN32
        return '\\';
#else
        return '/';
#endif
    }

    /**
     * The base dir for all the databases
     * @return the base dir
     */
    std::string dbBaseDir();

    std::string pathForDb(const std::string &dbname);

    bool exists(const std::string &path);

    std::string tablePath(const std::string &dbname, const std::string &tableName);

    /**
     *
     * @param dbname the dbname
     * @param tableName  the table name
     * @return the path to the table definition for a given table
     */
    std::string columndefinitionLocation(const std::string &dbname, const std::string &tableName);

    std::string tableDataLocation(const std::string &dbname, const std::string &tableName, int suffix);
}
#endif //TRIBBLEDB_FILEUTILS_H
