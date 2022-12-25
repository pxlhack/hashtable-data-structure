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

            if (isBusy(j) && this->arr[j]->getKey() == k) {
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
        this->arr[pos]->setKey(k);
        this->arr[pos]->setValue(data);
        this->arr[pos]->setBusy();
        this->size++;
        return true;
    }

    bool remove(string k) override {
        unsigned index = getIndex(k);
        if (index != -1) {
            this->arr[index]->setDeleted();
            this->size--;
            return true;
        }

        return false;
    }

    T get(string k) override {
        unsigned index = getIndex(k);
        if (index != -1) {
            return this->arr[index]->getValue();
        }

        throw "not found!";
    }

    void clear() override {
        for (OANode<T> *node: nodes) {
            if (node->isBusy()) {
                node->setDeleted();
            }
        }
    }

    string toString() override {
        stringstream sstr;
        for (int i = 0; i < this->capacity; ++i) {
            string stringView = "[";
            stringView += std::to_string(i);
            stringView += "] ";
            stringView += this->arr[i]->toString();
            sstr << stringView << endl;
        }
        return sstr.str();
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
        int j = -1;
        this->nodesCounter = 0;
        do {
            this->nodesCounter++;
            j = hashFunction(k, i);
            if (isBusy(j) && this->arr[j]->getKey() == k) {
                break;
            }
            i++;
        } while (i != this->capacity || !isFree(j));

        return j;
    }

};


#endif //HASHTABLE2_OA_FORM_H
