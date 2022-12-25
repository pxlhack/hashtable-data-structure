#ifndef HASHTABLE2_OA_FORM_H
#define HASHTABLE2_OA_FORM_H

#include <sstream>
#include "oa_node.h"
#include "table_form.h"

template<typename T>
class OAForm : public TableForm<T> {
public:
    OAForm(unsigned capacity) : TableForm<T>(capacity) {
        this->nodes = new OANode<T> *[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->nodes[i] = new OANode<T>();
        }
    }

    ~OAForm() {
        for (int i = 0; i < this->capacity; i++) {
            if (nodes[i] != nullptr) {
                delete nodes[i];
            }
            nodes[i] = nullptr;
        }
    }

    bool insert(string k, T data) override {
        int i = 0;
        int pos = -1;
        int j = hashFunction(k, i);
        this->nodesCounter = 0;


        while (i != this->capacity && !isFree(j)) {
            this->nodesCounter++;

            j = hashFunction(k, i);

            if (pos == -1 && isDeleted(j)) {
                pos = j;
            }

            if (isBusy(j) && this->nodes[j]->getKey() == k) {
                return false;
            }

            i++;
        }

        if (i == this->capacity && pos == -1) {
            return false;
        }

        if (pos == -1) {
            pos = j;
        }

        this->nodesCounter++;
        this->nodes[pos]->setKey(k);
        this->nodes[pos]->setData(data);
        this->nodes[pos]->setBusy();
        this->size++;
        return true;
    }

    bool remove(string k) override {
        unsigned index = getIndex(k);
        if (index != -1) {
            this->nodes[index]->setDeleted();
            this->size--;
            return true;
        }

        return false;
    }

    T get(string k) override {
        unsigned index = getIndex(k);
        if (index != -1) {
            return this->nodes[index]->getData();
        }

        throw "not found!";
    }

    void clear() override {
        for (int i = 0; i < this->capacity; ++i) {
            if (isBusy(i)) {
                this->nodes[i]->setDeleted();
            }
        }
    }

    string toString() override {
        stringstream sstr;
        for (int i = 0; i < this->capacity; ++i) {
            string stringView = "[";
            stringView += std::to_string(i);
            stringView += "] ";
            stringView += this->nodes[i]->toString();
            sstr << stringView << endl;
        }
        return sstr.str();
    }

    OANode<T> **getNodes() {
        return nodes;
    }

private:
    OANode<T> **nodes;

    int hashFunction(string str, int i) {
        return (this->hornerFunction(str) + i) % this->capacity;
    }

    bool isDeleted(int j) {
        return this->nodes[j]->isDeleted();
    }

    bool isBusy(int j) {
        return this->nodes[j]->isBusy();
    }

    bool isFree(int j) {
        return this->nodes[j]->isFree();
    }

    unsigned getIndex(string k) {
        int i = 0;
        int j;
        this->nodesCounter = 0;
        do {
            this->nodesCounter++;
            j = hashFunction(k, i);
            if (isBusy(j) && this->nodes[j]->getKey() == k) {
                return j;
            }
            i++;
        } while (i != this->capacity || !isFree(j));

        return -1;
    }

};


#endif //HASHTABLE2_OA_FORM_H
