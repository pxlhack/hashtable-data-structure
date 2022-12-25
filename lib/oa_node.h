#ifndef HASHTABLE2_OA_NODE_H
#define HASHTABLE2_OA_NODE_H

#include "node.h"

enum states {
    FREE,
    BUSY,
    DELETED
};

template<typename T>
class OANode : public Node<T> {

public:
    OANode() {
        state = states::FREE;
    }

    void setDeleted() {
        this->state = states::DELETED;
    }

    void setBusy() {
        this->state = states::BUSY;
    }

    bool isFree() {
        return state == states::FREE;
    }

    bool isBusy() {
        return state == states::BUSY;
    }

    bool isDeleted() {
        return state == states::DELETED;
    }

    string toString() override {
        string states[] = {"FREE", "BUSY", "DELETED"};
        string stringView = "(" + states[state] + ") ";
        if (isBusy()) {
            stringView += "Key: " + this->key + " " + "Data: " + to_string(this->data);
        }
        return stringView;
    }

private:
    states state;
};


#endif //HASHTABLE2_OA_NODE_H
