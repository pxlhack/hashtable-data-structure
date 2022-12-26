#include "lib/hash_table.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "lib/user_menu.h"

using namespace std;

double teorCL(int n, int m) { return 1 + ((double) n / (double) m) / 2; }

double sucTeorOA(int n, int m) {
    double a = (double) n / (double) m;
    return (1 + 1 / (1 - a)) / 2;
}

double unsucTeorOA(int n, int m) {
    double a = (double) n / (double) m;
    return (1 + 1 / pow((1 - a), 2)) / 2;
}

string newStr(int num) {
    string str;
    for (int i = 0; i < num; i++)
        str += 'A' + rand() % 26;
    return str;
}

int main() {
    int n, m = 1000;
    int step = m / 20;
    vector<string> keys;
    vector<double> alphas;
    vector<double> insert_c;
    vector<double> search_c;
    vector<double> remove_c;
    vector<double> theoretical;
    for (int i = 0; i < 1.5 * m / step; i++) {
        insert_c.push_back(0);
        search_c.push_back(0);
        remove_c.push_back(0);
    }
    cout << "step = " << step << "\n";
    for (int j = 0; j < 10; j++) {
        HashTable<int> ccHashTable(m);
        for (int k = 0; ccHashTable.getSize() <= 1.5 * (double) m; k++) {
            n = ccHashTable.getSize();
            if (alphas.size() <= 1.5 * m / step)
                alphas.push_back((double) n / (double) m);
            string key = rndString();
            ccHashTable.insert(key, 1);
            insert_c[k] += ccHashTable.getNodesNumber();
            ccHashTable.get(key);
            search_c[k] += ccHashTable.getNodesNumber();
            ccHashTable.remove(key);
            remove_c[k] += ccHashTable.getNodesNumber();
            if (theoretical.size() <= 1.5 * m / step)
                theoretical.push_back(teorCL(n, m));
            for (int i = 0; i < step; i++) {
                string str = rndString();
                keys.push_back(str);
                ccHashTable.insert(str, 0);
            }
        }
    }
    cout << "ccHashTable, m = " << m << "\n";
    cout << "alpha: ";
    for (int i = 0; i < alphas.size() - 1; i++)
        cout << alphas[i] << ", ";
    cout << "\ninsert: ";
    for (double i: insert_c)
        cout << i / 10 << ", ";
    cout << "\nsearch: ";
    for (double i: search_c)
        cout << i / 10 << ", ";
    cout << "\nremove: ";
    for (double i: remove_c)
        cout << i / 10 << ", ";
    cout << "\ntheoretical: ";
    for (int i = 0; i < theoretical.size() - 1; i++)
        cout << theoretical[i] << ", ";
    alphas.clear();
    insert_c.clear();
    search_c.clear();
    remove_c.clear();
    for (int i = 0; i < m / step; i++) {
        insert_c.push_back(0);
        search_c.push_back(0);
        remove_c.push_back(0);
    }
    theoretical.clear();
    for (int j = 0; j < 10; j++) {
        HashTable<int> oaHashTable(m, false);
        for (int k = 0; oaHashTable.getSize() < m; k++) {
            n = oaHashTable.getSize();
            if (alphas.size() <= m / step)
                alphas.push_back((double) n / (double) m);
            string key = rndString();
            oaHashTable.insert(key, 1);
            insert_c[k] += oaHashTable.getNodesNumber();
            oaHashTable.get(key);
            search_c[k] += oaHashTable.getNodesNumber();
            oaHashTable.remove(key);
            remove_c[k] += oaHashTable.getNodesNumber();
            if (theoretical.size() <= m / step)
                theoretical.push_back(unsucTeorOA(n, m));
            for (int i = 0; i < step; i++) {
                string str = rndString();
                keys.push_back(str);
                oaHashTable.insert(str, 0);
            }
        }
    }
    cout << "\n\noaHashTable, m = " << m << "\n";
    cout << "alpha: ";
    for (int i = 0; i < alphas.size() - 1; i++)
        cout << alphas[i] << ", ";
    cout << "\ninsert: ";
    for (double i: insert_c)
        cout << i / 10 << ", ";
    cout << "\nsearch: ";
    for (double i: search_c)
        cout << i / 10 << ", ";
    cout << "\nremove: ";
    for (double i: remove_c)
        cout << i / 10 << ", ";
    cout << "\ntheoretical: ";
    for (int i = 0; i < theoretical.size() - 1; i++)
        cout << theoretical[i] << ", ";

    return 0;
}