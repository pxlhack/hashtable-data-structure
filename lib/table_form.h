#ifndef HASHTABLE2_TABLE_FORM_H
#define HASHTABLE2_TABLE_FORM_H

#include <string>
#include <cmath>
#include <sstream>

using namespace std;


template<typename T>
class TableForm {
public:
    TableForm(unsigned capacity) {
        this->capacity = capacity;
        this->size = 0;
    }

    ~TableForm() {}

    virtual bool insert(string k, T data) = 0;

    virtual bool remove(string k) = 0;

    virtual T get(string k) = 0;

    virtual void clear() = 0;

    virtual string toString() = 0;



    bool isEmpty() {
        return this->size == 0;
    };

    unsigned getCapacity() {
        return this->capacity;
    }

    unsigned getSize() {
        return this->size;
    }

    unsigned getNodesNumber() {
        return this->nodesCounter;
    }

    int hornerFunction(string str) {
        unsigned k = 0;
        for (unsigned i = 0; i < str.size(); ++i) {
            k += pow(32, str.size() - 1 - i) * (str.at(i) - 'A' + 1);
        }

        double g_r = 0.6180339887;

        double X = g_r * k;
        X = X - (unsigned) X;
        return (unsigned) (X * this->capacity);
    }

protected:
    unsigned size;
    unsigned capacity;
    unsigned nodesCounter;
};


#endif //HASHTABLE2_TABLE_FORM_H
