#ifndef PASSWORDRECORD_H
#define PASSWORDRECORD_H

#include <iostream>
#include <string>
#include <ctime>

class PasswordRecord {
private:
    std::string value;
    std::string hash;   // placeholder for hashed password
    std::time_t timestamp;

public:
    PasswordRecord(const std::string& pwd);
    std::string getValue() const;
    std::string getHash() const;
    std::time_t getTimestamp() const;
    void display() const;
};

#endif