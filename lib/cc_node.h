#ifndef HASHTABLE2_CC_NODE_H
#define HASHTABLE2_CC_NODE_H

#include "node.h"

template<typename T>
class CCNode : public Node<T> {
public:
    CCNode() {
        this->next = nullptr;
    }

    CCNode *getNext() const {
        return next;
    }

    void setNext(CCNode *node) {
        this->next = node;
    }

private:
    CCNode *next;
};

#endif //HASHTABLE2_CC_NODE_H
