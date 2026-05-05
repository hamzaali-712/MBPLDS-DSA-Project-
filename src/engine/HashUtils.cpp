#include "HashUtils.h"
#include <sstream>
#include <iomanip>
#include <functional>

std::string HashUtils::generateSHA256(const std::string& input) {
    // Academic mock of SHA-256 using standard hash and hex formatting
    // A real SHA-256 implementation would use block processing.
    std::hash<std::string> hasher;
    size_t hashVal = hasher(input);
    
    // We mix it to generate 64 hex characters (256 bits)
    std::stringstream ss;
    for(int i = 0; i < 4; i++) {
        ss << std::hex << std::setw(16) << std::setfill('0') << (hashVal ^ (i * 0x5bd1e9955bd1e995));
    }
    return ss.str();
}
