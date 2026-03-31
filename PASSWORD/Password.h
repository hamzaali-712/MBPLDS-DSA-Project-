#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <string>
#include <ctime>

class Password {
private:
    std::string value;
    std::string hash;   // placeholder for hashed password
    std::time_t timestamp;

public:
    Password(const std::string& pwd);
    std::string getValue() const;
    std::string getHash() const;
    std::time_t getTimestamp() const;
    void display() const;
};

#endif