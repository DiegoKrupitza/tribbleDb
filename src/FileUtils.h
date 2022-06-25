#include <string>
#include <cstdlib>

#ifndef MYSMALLDB_FILEUTILS_H
#define MYSMALLDB_FILEUTILS_H

namespace MySmallDb::FileUtils {


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

}
#endif //MYSMALLDB_FILEUTILS_H
