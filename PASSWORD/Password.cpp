#include "Password.h"
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm> // <--- Add this

// Simple hash mock (for now just reversing string)
std::string mockHash(const std::string& pwd) {
    std::string hashed = pwd;
    std::reverse(hashed.begin(), hashed.end());
    return hashed;
}

Password::Password(const std::string& pwd) {
    value = pwd;
    hash = mockHash(pwd);
    timestamp = std::time(nullptr);
}

std::string Password::getValue() const { return value; }
std::string Password::getHash() const { return hash; }
std::time_t Password::getTimestamp() const { return timestamp; }

void Password::display() const {
    std::cout << "Password: " << value 
              << ", Hash: " << hash 
              << ", Timestamp: " << timestamp << std::endl;
}