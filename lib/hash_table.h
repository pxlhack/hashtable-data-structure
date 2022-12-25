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

    bool isCollisionsChain() {
        return dynamic_cast<CCForm<T> *>(table);
    }


    void toCollisionsChain() {
        OAForm<T> *oatable = (OAForm<T> *) table;
        OANode<T> **nodes = oatable->getNodes();
        CCForm<T> *cltable = new CCForm<T>(getCapacity());
        for (int i = 0; i < getCapacity(); i++) {
            if (nodes[i]->isBusy()) {
                cltable->insert(nodes[i]->getKey(), nodes[i]->getData());
            }
        }
        table = cltable;
        delete oatable;
    }

    void toOpenAddressing() {
        CCForm<T> *cltable = (CCForm<T> *) table;
        CCNode<T> **nodes = cltable->getNodes();
        OAForm<T> *oatable = new OAForm<T>(getCapacity());
        for (int i = 0; i < getCapacity(); i++) {
            if (nodes[i] != nullptr) {
                oatable->insert(nodes[i]->getKey(), nodes[i]->getData());
                CCNode<T> *t = nodes[i]->getNext();
                while (t != nullptr) {
                    oatable->insert(t->getKey(), t->getData());
                    t = t->getNext();
                }
            }
        }
        table = oatable;
        delete cltable;
    }


private:
    TableForm<T> *table;
};


#endif //HASHTABLE2_HASH_TABLE_H
