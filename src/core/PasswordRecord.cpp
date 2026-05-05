#include "PasswordRecord.h"
#include "../engine/HashUtils.h"
#include <iostream>
#include <string>
#include <ctime>

PasswordRecord::PasswordRecord(const std::string& pwd) {
    value = pwd;
    hash = HashUtils::generateSHA256(pwd);
    timestamp = std::time(nullptr);
}

std::string PasswordRecord::getValue() const { return value; }
std::string PasswordRecord::getHash() const { return hash; }
std::time_t PasswordRecord::getTimestamp() const { return timestamp; }

void PasswordRecord::display() const {
    std::cout << "Password: " << value 
              << ", Hash: " << hash 
              << ", Timestamp: " << timestamp << std::endl;
}