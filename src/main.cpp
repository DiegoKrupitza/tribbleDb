#include <iostream>
#include <vector>
#include "FileUtils.h"
#include "Database.h"
#include "ColumnDefinition.h"

using namespace tribbleDb;


int main() {
    std::cout << FileUtils::dbBaseDir() << std::endl;

    /*Database mySmallDb = Database::createEmpty("test");

    ColumnDefinition primaryKey{"id", true, INT,{}};
    ColumnDefinition nameField{"name", false, TEXT,{}};

    std::vector<ColumnDefinition> columns{primaryKey, nameField};
    const Table &testTable = mySmallDb.createTable("people", columns);

     */

    Database db = Database::load("test");
    Table &testTable = db.getTable("people");

    std::cout << testTable.toString() << std::endl;

    testTable.insert({
                             {"id",   "1"},
                             {"name", "Diego"}
                     }
    );

    return 0;
}
