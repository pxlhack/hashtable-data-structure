#ifndef HASHTABLE2_TABLE_FORM_H
#define HASHTABLE2_TABLE_FORM_H

#include <string>

using namespace std;

#define DEFAULT_SIZE 16

template<typename T>
class TableForm {
public:
    TableForm(unsigned capacity = DEFAULT_SIZE) {
        this->capacity = capacity;
        this->size = 0;
    }

    ~TableForm() {}

    virtual bool insert(string k, T data) = 0;

    virtual bool remove(string k) = 0;

    virtual T get(string K) = 0;

    virtual void clear() = 0;

    virtual void toString() = 0;

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


protected:
    unsigned size;
    unsigned capacity;
    unsigned nodesCounter;
};


#endif //HASHTABLE2_TABLE_FORM_H
