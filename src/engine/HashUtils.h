#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <string>

class HashUtils {
public:
    // Generates a mock 64-character SHA-256 style hash based on input string
    static std::string generateSHA256(const std::string& input);
};

#endif
