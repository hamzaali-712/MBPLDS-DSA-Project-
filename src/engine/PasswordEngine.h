#ifndef PASSWORDENGINE_H
#define PASSWORDENGINE_H

#include <string>

class PasswordEngine {
public:
    static bool meetsComplexityRequirements(const std::string& pwd);
    static int calculatePoolSize(const std::string& pwd);
    static double calculateEntropy(const std::string& pwd);
    static double calculateCrackTimeSeconds(const std::string& pwd);
};

#endif
