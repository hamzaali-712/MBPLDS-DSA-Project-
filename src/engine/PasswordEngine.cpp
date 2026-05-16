#include "PasswordEngine.h"
#include <regex>
#include <cmath>

bool PasswordEngine::meetsComplexityRequirements(const std::string& pwd) {
    if (pwd.length() < 6 || pwd.length() > 50) return false;
    
    // Academic complexity: must contain at least one letter and one number
    std::regex alpha("[A-Za-z]");
    std::regex digit("[0-9]");
    
    return std::regex_search(pwd, alpha) && std::regex_search(pwd, digit);
}

int PasswordEngine::calculatePoolSize(const std::string& pwd) {
    int pool = 0;
    if (std::regex_search(pwd, std::regex("[a-z]"))) pool += 26;
    if (std::regex_search(pwd, std::regex("[A-Z]"))) pool += 26;
    if (std::regex_search(pwd, std::regex("[0-9]"))) pool += 10;
    if (std::regex_search(pwd, std::regex("[^a-zA-Z0-9]"))) pool += 32;
    if (pool == 0) pool = 26; // Fallback
    return pool;
}

double PasswordEngine::calculateEntropy(const std::string& pwd) {
    int pool = calculatePoolSize(pwd);
    return pwd.length() * (log(pool) / log(2));
}

double PasswordEngine::calculateCrackTimeSeconds(const std::string& pwd) {
    double entropy = calculateEntropy(pwd);
    double attempts = pow(2, entropy);
    // Assume a modern GPU array testing 10 Billion hashes per second
    double hashesPerSecond = 10000000000.0;
    return attempts / hashesPerSecond;
}
