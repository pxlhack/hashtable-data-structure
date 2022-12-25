#ifndef HASHTABLE2_OA_FORM_H
#define HASHTABLE2_OA_FORM_H

#include <vector>
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



private:
    OANode<T> **nodes;
};


#endif //HASHTABLE2_OA_FORM_H
