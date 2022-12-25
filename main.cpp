#include <iostream>
#include "lib/hash_table.h"

int main() {
    HashTable<int> table;
    table.insert("ALPHA", 3);
    table.insert("BETA", 3);
    table.insert("GAMMA", 3);
    table.print();
    table.toOpenAddressing();
    table.print();
    table.toCollisionsChain();
    table.print();
    table.toOpenAddressing();
    table.print();
    return 0;
}
