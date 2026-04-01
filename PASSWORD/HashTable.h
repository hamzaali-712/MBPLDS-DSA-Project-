#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    std::list<std::string> table[TABLE_SIZE];

    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char ch : key) hash += ch;
        return hash % TABLE_SIZE;
    }

public:
    void insert(const std::string& pwd) {
        int index = hashFunction(pwd);
        table[index].push_back(pwd);
    }

    bool isLeaked(const std::string& pwd) {
        int index = hashFunction(pwd);
        for (const std::string& s : table[index]) {
            if (s == pwd) return true;
        }
        return false;
    }
};

#endif
