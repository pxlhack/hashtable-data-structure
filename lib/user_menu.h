#ifndef HASHTABLE2_USER_MENU_H
#define HASHTABLE2_USER_MENU_H

#include <iostream>
#include "regex"
#include <exception>
#include <ctime>
#include "hash_table.h"

using namespace std;

#define HELP "Menu:\n\
1) Create new empty HashTable\n\
2) Create new HashTable and random fill\n\
3) To collisions chain\n\
4) To open addressing\n\
5) Insert new value with key to table\n\
6) Remove value with key\n\
7) Print the table\n\
8) Show size\n\
9) Show capacity\n\
10) Check the table for emptiness\n\
11) Get value with key\n\
12) Clear table\n\
13) Iterators\n\
14) Count of values in previous operation\n\
0) Exit\n"

bool isPositiveValue(string_view s) {
    static const regex r(R"(\d{1,})");
    return regex_match(s.data(), r);
}

bool isNegativeValue(std::string_view s) {
    static const regex r(R"(-\d{1,})");
    return regex_match(s.data(), r);
}

string getPositiveValueAsString(const string &desiredValue) {
    string str;
    bool flag = true;

    do {
        cout << "Enter the " << desiredValue << ":";
        cin >> str;

        if (str == "e") break;
        if (isPositiveValue(string_view(str))) {
            flag = false;
        } else {
            cout << "Not a number!\n\n";
        }
    } while (flag);
    return str;
}

string getIntegerValueAsString(const string &desiredValue) {
    string str;
    bool flag = true;

    do {
        cout << "Enter the " << desiredValue << ":";
        cin >> str;

        if (str == "e") break;
        if (isPositiveValue(string_view(str)) || isNegativeValue(string_view(str))) {
            flag = false;
        } else {
            cout << "Not a number!\n\n";
        }
    } while (flag);
    return str;
}

bool setValueFromString(int *value) {
    string valueString = getIntegerValueAsString("value");
    if (valueString == "e") {
        return true;
    }
    *value = stoul(valueString);
    return false;
}

bool setKeyFromString(int *key) {
    string positionString = getIntegerValueAsString("key");
    if (positionString == "e") {
        return true;
    }
    *key = stoul(positionString);
    return false;
}

bool isValidCommand(const string &command) {
    return isPositiveValue(std::string_view(command));
}

bool isUpperCase(string k) {
    for (int i = 0; i < k.size(); i++)
        if (k[i] >= 'a' && k[i] <= 'z')
            return false;
    return true;
}

string rndString() {
    string s = "";

    for (int i = 0; i < rand() % 15 + 5; i++)
        s += ('A' + rand() % ('Z' - 'A'));

    return s;
}

void fillRandom(HashTable<int> *ht, int n) {

    for (int i = 0; i < n; i++)
        ht->insert(rndString(), rand() % 10);

}

void testMenu() {

    HashTable<int> *ht = nullptr;

    bool isWorked = true;
    string command;

    do {

        cout << HELP;
        cout << ">";
        cin >> command;

        if (isValidCommand(command)) {
            int num = stoul(command);

            switch (num) {

                case 1: {
                    ht = new HashTable<int>();
                    cout << "~~ Created a empty HashTable ~~\n\n";
                    break;
                }

                case 2: {
                    ht = new HashTable<int>();
                    fillRandom(ht, 10);
                    cout << "~~ Created a table with size: " << ht->getSize() << " ~~\n";
                    ht->print();
                    break;
                }


                case 3: {
                    if (ht != nullptr) {
                        ht->toCollisionsChain();
                        cout << "~~ HashTable has a collisions chain ~~\n";
                        break;
                    }

                    cout << "-- HashTable is nullptr --\n";
                    break;
                }


                case 4: {
                    if (ht != nullptr) {
                        ht->toOpenAddressing();
                        cout << "~~ HashTable has a open addressing ~~\n";
                        break;
                    }

                    cout << "~~ HashTable is nullptr ~~\n";
                    break;
                }


                case 5: {
                    if (ht != nullptr) {
                        string k;

                        do {
                            cout << "Enter key:\n>";
                            cin >> k;

                            if (!isUpperCase(k)) {
                                cout << "~~ Error, use only upper case char ~~\n";
                            }

                        } while (!isUpperCase(k));

                        string v = getIntegerValueAsString("value");
                        if (v == "e") {
                            break;
                        }

                        int val = stoul(v);

                        if (ht->insert(k, val)) {
                            cout << "~~ " << k << ": " << v << " insert to table ~~\n";
                        } else {
                            cout << "~~ Value is not inserted to table ~~\n";
                        }
                    } else
                        cout << "~~ HashTable is nullptr ~~\n";
                }
                    break;

                case 6: {

                    if (ht != nullptr) {

                        string k;

                        do {
                            cout << "Enter key:\n>";
                            cin >> k;

                            if (!isUpperCase(k))
                                cout << "~~ Error, use only upper case char ~~\n";

                        } while (!isUpperCase(k));

                        if (!ht->remove(k)) {
                            cout << "~~ Key '" << k << "' is not exist ~~\n";
                        }

                    } else {
                        cout << "~~ HashTable is nullptr ~~\n";
                    }

                }
                    break;

                case 7: {

                    if (ht != nullptr) {
                        ht->print();
                    } else {
                        cout << "~~ HashTable is nullptr ~~\n";
                    }

                }
                    break;

                case 8: {

                    if (ht != nullptr)
                        cout << "~~ Size: " << ht->getSize() << " ~~\n";
                    else
                        cout << "~~ HashTable is nullptr ~~\n";

                }
                    break;

                case 9: {

                    if (ht != nullptr)
                        cout << "~~ Capacity: " << ht->getCapacity() << " ~~\n";
                    else
                        cout << "~~ HashTable is nullptr ~~\n";

                }
                    break;

                case 10: {

                    if (ht != nullptr) {
                        if (ht->isEmpty())
                            cout << "~~ HashTable is empty ~~\n";
                        else
                            cout << "~~ HashTable is not empty ~~\n";
                    } else
                        cout << "~~ HashTable is nullptr ~~\n";

                }
                    break;

                case 11: {

                    if (ht != nullptr) {

                        string k;

                        do {
                            cout << "Enter key:\n>";
                            cin >> k;

                            if (!isUpperCase(k))
                                cout << "~~ Error, use only upper case char ~~\n";

                        } while (!isUpperCase(k));

                        cout << "~~ Value: " << ht->get(k) << ", by key: " << k << " ~~\n";

                    } else
                        cout << "~~ HashTable is nullptr ~~\n";

                }
                    break;

                case 12: {

                    if (ht != nullptr)
                        ht->clear();
                    else
                        cout << "~~ HashTable is nullptr ~~\n";

                }
                    break;

                    //ITERATOR
                case 13: {
                    if (ht == nullptr) {
                        cout << "-- Table not created --\n\n";
                        break;
                    }

                    if (ht->isEmpty()) {
                        cout << "-- Table is empty --\n\n";
                        break;
                    }


                    bool isIteratorsWorked = true;
                    string iteratorsCommand;

                    auto it1 = ht->begin();
                    do {
                        cout << "1) ++\n2) *\n3) begin\n4) end\n5) print\n0) exit\n";
                        cout << ">";
                        cin >> iteratorsCommand;
                        if (isPositiveValue(std::string_view(iteratorsCommand))) {
                            int i_num = stoul(iteratorsCommand);
                            switch (i_num) {
                                case 1 : {
                                    if (it1 == ht->end()) {
                                        cout << "iterator is not set\n";
                                    } else {
                                        ++it1;
                                    }

                                    break;
                                }

                                case 2: {
                                    if (it1 == ht->end()) {
                                        cout << "iterator is not set\n";
                                    } else {
                                        cout << (*it1).toString() << endl;
                                    }

                                    break;
                                }
                                case 3: {
                                    it1 = ht->begin();
                                    break;
                                }
                                case 4: {
                                    it1 = ht->end();
                                    break;
                                }
                                case 5: {
                                    auto it2 = ht->begin();
                                    while (it2 != ht->end()) {
                                        cout << (*it2).toString() << endl;
                                        ++it2;
                                    }
                                    cout << endl;

                                    break;
                                }
                                case 0: {
                                    isIteratorsWorked = false;
                                    break;
                                }
                                default: {
                                    cout << "!!! unknown command: " << iteratorsCommand << " !!!" << endl;
                                    break;
                                }
                            }
                        } else {
                            cout << "!!! unknown command: " << iteratorsCommand << " !!!" << endl;
                        }

                    } while (isIteratorsWorked);
                    break;
                }
                    break;

                case 14: {
                    //COUNT
                }
                    break;

                case 0: {
                    isWorked = false;
                }
                    break;
                default:
                    cout << "!!! unknown command: " << command << " !!!" << endl;
                    break;
            }

        }

    } while (isWorked);
}


#endif //HASHTABLE2_USER_MENU_H
