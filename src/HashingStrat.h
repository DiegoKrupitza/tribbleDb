#ifndef MYSMALLDB_HASHINGSTRAT_H
#define MYSMALLDB_HASHINGSTRAT_H


namespace MySmallDb {
    enum HashingStrategy {
        MODULO = 0
    };

    int hash(HashingStrategy hashingStrategy);

}
#endif //MYSMALLDB_HASHINGSTRAT_H
