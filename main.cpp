#include <iostream>
#include "lib/hash_table.h"


//todo iterators
//todo increase size after form changing
//todo hashing test
//todo complexity test
//todo readme.md
//todo menu

//todo clear cc_form.h
//todo toString ccnode.h

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

//    auto it = table.begin();
//    while (it != table.end()) {
//        cout << *it << endl;
//    }
    return 0;
}
