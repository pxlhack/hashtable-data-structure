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

    Node<T> **getNodes() {
        return table->getNodes();
    }

    bool isCollisionsChain() {
        return dynamic_cast<CCForm<T> *>(table);
    }

    void toCollisionsChain() {
        if (!isCollisionsChain()) {

            OAForm<T> *pOaForm = (OAForm<T> *) table;
            Node<T> **nodes = getNodes();
            CCForm<T> *pCcForm = new CCForm<T>(getCapacity());

            for (int i = 0; i < getCapacity(); i++) {
                if (static_cast<OANode<T> *>(nodes[i])->isBusy()) {
                    pCcForm->insert(nodes[i]->getKey(), nodes[i]->getData());
                }
            }
            table = pCcForm;
            delete pOaForm;
        }
    }

    void toOpenAddressing() {
        if (isCollisionsChain()) {

            CCForm<T> *pCcForm = (CCForm<T> *) table;
            Node<T> **nodes = getNodes();
            OAForm<T> *pOaForm = new OAForm<T>(getCapacity());

            for (int i = 0; i < getCapacity(); i++) {
                if (nodes[i] != nullptr) {

                    pOaForm->insert(nodes[i]->getKey(), nodes[i]->getData());
                    CCNode<T> *t = static_cast<CCNode<T> *>(nodes[i])->getNext();

                    while (t != nullptr) {
                        pOaForm->insert(t->getKey(), t->getData());
                        t = t->getNext();
                    }
                }
            }

            table = pOaForm;
            delete pCcForm;
        }
    }


    class Iterator {
    public:

        Iterator(HashTable<T> *_p, Node<T> *cc_c, int i_) : ptr(_p), cur(cc_c), i(i_) {
        }

        Iterator(HashTable<T> *_p, bool begin = false) : ptr(_p), i(0) {
            if (begin) {
                if (ptr->getSize() == 0)
                    cur = nullptr;
                else {
                    while (!static_cast<OANode<T> *>(ptr->getNodes()[i])->isBusy()) {
                        i++;
                    }
                    cur = ptr->getNodes()[i];
                }
            } else {
                cur = nullptr;
            }
        }


        Iterator operator++() {
            if (ptr->isCollisionsChain()) {
                nextCCNode();
            } else {
                nextOANOde();
            }
        }

        bool operator==(Iterator it) {
            return this->cur == it.cur;
        }

        bool operator!=(Iterator it) {
            return this->cur != it.cur;
        }

        Node<T> operator*() {
            if (!cur || i == ptr->getCapacity()) {
                throw "iterator is not setted";
            }
            return *cur;
        }


    private:
        HashTable<T> *ptr;
        int i;
        Node<T> *cur;

        void nextCCNode() {
            if (!cur || i == ptr->getCapacity()) return;
            if (static_cast<CCNode<T> *>(cur)->getNext()) {
                cur = static_cast<CCNode<T> *>(cur)->getNext();
                return;
            }
            do {
                cur = static_cast<CCNode<T> *>(ptr->getNodes()[++i]);
                if (cur) {
                    break;
                }
            } while (i != ptr->getCapacity());
        }

        void nextOANOde() {
            if (!cur) {
                return;
            }

            while (i != ptr->getCapacity()) {
                cur = static_cast<OANode<int> *>(ptr->getNodes()[++i]);

                if (i == ptr->getCapacity()) {
                    break;
                }
                if (static_cast<OANode<int> *>(cur)->isBusy()) {
                    break;
                }

            }
        }

    };

    Iterator begin() {
        if (isCollisionsChain()) {
            Node<T> **test = this->getNodes();
            Node<T> *_cur;
            for (int i = 0; i < this->getCapacity(); i++) {
                _cur = test[i];
                if (_cur) {
                    return Iterator(this, _cur, i);
                }
            }
            return end();
        } else {
            return Iterator(this, true);
        }

    }

    Iterator end() {
        if (isCollisionsChain()) {
            return Iterator(this, nullptr, 0);
        } else {
            return Iterator(this, false);
        }
    }


    unsigned getNodesNumber() {
        return table->getNodesNumber()

        ;
    }

private:
    TableForm<T> *table;
};


#endif //HASHTABLE2_HASH_TABLE_H
