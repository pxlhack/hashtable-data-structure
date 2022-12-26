#ifndef HASHTABLE2_NODE_H
#define HASHTABLE2_NODE_H

#include <string>

using namespace std;

template<typename T>
class Node {
public:
    string getKey() const {
        return key;
    }

    void setKey(string key) {
        this->key = key;
    }

    T getData() const {
        return data;
    }

    void setData(T data) {
        this->data = data;
    }

    string toString() {
        return "Key: " + this->key + "; Data: " + to_string(this->data);
    };


protected:
    string key;
    T data;
};


#endif //HASHTABLE2_NODE_H
