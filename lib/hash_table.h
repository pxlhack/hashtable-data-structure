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
        OAForm<T> *pOaForm = (OAForm<T> *) table;
        OANode<T> **nodes = pOaForm->getNodes();
        CCForm<T> *pCcForm = new CCForm<T>(getCapacity());
        for (int i = 0; i < getCapacity(); i++) {
            if (nodes[i]->isBusy()) {
                pCcForm->insert(nodes[i]->getKey(), nodes[i]->getData());
            }
        }
        table = pCcForm;
        delete pOaForm;
    }

    void toOpenAddressing() {
        CCForm<T> *pCcForm = (CCForm<T> *) table;
        CCNode<T> **nodes = pCcForm->getNodes();
        OAForm<T> *pOaForm = new OAForm<T>(getCapacity());
        for (int i = 0; i < getCapacity(); i++) {
            if (nodes[i] != nullptr) {
                pOaForm->insert(nodes[i]->getKey(), nodes[i]->getData());
                CCNode<T> *t = nodes[i]->getNext();
                while (t != nullptr) {
                    pOaForm->insert(t->getKey(), t->getData());
                    t = t->getNext();
                }
            }
        }
        table = pOaForm;
        delete pCcForm;
    }



private:
    TableForm<T> *table;
};


#endif //HASHTABLE2_HASH_TABLE_H
