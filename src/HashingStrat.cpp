#include "HashingStrat.h"

using namespace MySmallDb;

int hash(HashingStrategy hashingStrategy, int val) {
    //TODO: implement various hash modes
    return val % 5;
}