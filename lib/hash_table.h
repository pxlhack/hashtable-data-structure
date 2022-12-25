#ifndef HASHTABLE2_HASH_TABLE_H
#define HASHTABLE2_HASH_TABLE_H

#include "table_form.h"
#include "oa_form.h"
#include "cc_form.h"

#define DEFAULT_SIZE 16

template<typename T>
class HashTable {
public:
    HashTable(int capacity = DEFAULT_SIZE, bool ccform = true) {
        if (ccform) {
            table = new CCForm<T>(capacity);
        } else {
            table = new OAForm<T>(capacity);

        }
    }

    bool insert(string k, T data) {
        return table->insert(k, data);
    }

    bool remove(string k) {
        return table->remove(k);
    }

    T get(string k) {
        return table->get(k);
    }

    bool isEmpty() {
        return table->isEmpty();
    }

    int getSize() {
        return table->getSize();
    }

    int getCapacity() {
        return table->getCapacity();
    }

    void clear() {
        table->clear();
    }

    void print() {
        cout << table->toString() << endl;
    }


private:
    TableForm<T> *table;
};


#endif //HASHTABLE2_HASH_TABLE_H
