#ifndef HASHTABLE2_CC_FORM_H
#define HASHTABLE2_CC_FORM_H


#include "table_form.h"
#include "cc_node.h"

template<typename T>
class CCForm : public TableForm<T> {
public:
    CCForm(unsigned capacity) : TableForm<T>(capacity) {
        this->nodes = new CCNode<T> *[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->nodes[i] = nullptr;
        }
    }

    ~CCForm() {
        for (int i = 0; i < this->capacity; i++) {
            if (this->nodes[i] != nullptr) {
                delete this->nodes[i];
            }
            this->nodes[i] = nullptr;
        }
    }

    bool insert(string k, T data) override {
        int j = this->hornerFunction(k);
        if (this->nodes[j] == nullptr) {
            this->nodesCounter++;
            this->nodes[j] = new CCNode<T>();
            this->nodes[j]->setData(data);
            this->nodes[j]->setKey(k);
        } else {
            CCNode<T> *p = this->nodes[j];
            if (p->getKey() == k) {
                return false;
            }
            while (p->getNext() != nullptr) {
                this->nodesCounter++;
                p = p->getNext();
                if (p->getKey() == k) {
                    return false;
                }
            }
            p->setNext(new CCNode<T>());
            p->getNext()->setNext(nullptr);
            p->getNext()->setKey(k);
            p->getNext()->setData(data);
        }
        this->size++;
        return true;
    }

    bool remove(string k) override {

        int j = this->hornerFunction(k);

        CCNode<T> *p = this->nodes[j];

        if (p == nullptr) {
            return false;
        }
        if (p->getKey() == k) {
            this->nodes[j] = this->nodes[j]->getNext();
            delete p;
            this->size--;
            return true;
        }

        while (p->getNext() != nullptr) {
            this->nodesCounter++;
            if (p->getNext()->getKey() == k)
                break;
            p = p->getNext();
        }
        if (p->getNext() == nullptr) {
            return false;
        }
        CCNode<T> *t = p->getNext();
        p->setNext(p->getNext()->getNext());
        delete t;
        this->size--;
        return true;
    }

    T get(string k) override {
        int j = this->hornerFunction(k);
        CCNode<T> *t = this->nodes[j];
        while (t != nullptr) {
            if (t->getKey() == k) {
                break;
            }
            t = t->getNext();
        }
        if (t == nullptr)
            throw "not found!";
        return t->getData();
    }

    void clear() override {

    }

    string toString() override {
        stringstream sstr;
        for (int i = 0; i < this->capacity; i++) {
            if (this->nodes[i] != nullptr) {
                sstr << i << " - " << this->nodes[i]->getKey();
                CCNode<T> *t = this->nodes[i]->getNext();
                while (t != nullptr) {
                    sstr << ", " << t->getKey();
                    t = t->getNext();
                }
                sstr << "\n";
            } else
                sstr << i << " - Empty\n";
        }
        return sstr.str();
    }

    CCNode<T> **getNodes() {
        return nodes;
    }

private:
    CCNode<T> **nodes;
};


#endif //HASHTABLE2_CC_FORM_H
