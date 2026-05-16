#include "ui/CLI.h"
#include "engine/PasswordEngine.h"
#include "datastructures/WeakPasswordTrie.h"
#include "datastructures/LeakHashTable.h"
#include "engine/HashUtils.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Check if running in API mode for Streamlit
    if (argc == 3 && std::string(argv[1]) == "--analyze") {
        std::string password = argv[2];
        
        // Load weak passwords
        WeakPasswordTrie weakPasswords;
        std::ifstream weakFile("data/weak_passwords.txt");
        if (weakFile.is_open()) {
            std::string line;
            while (std::getline(weakFile, line)) {
                if (!line.empty()) {
                    if (line.back() == '\r') line.pop_back();
                    weakPasswords.insert(line);
                }
            }
            weakFile.close();
        } else {
            weakPasswords.insert("password");
            weakPasswords.insert("admin");
            weakPasswords.insert("qwerty");
            weakPasswords.insert("123456");
        }

        // Load leaked hashes
        LeakHashTable leakDB;
        std::ifstream leakFile("data/leaked_hashes.txt");
        if (leakFile.is_open()) {
            std::string line;
            while (std::getline(leakFile, line)) {
                if (!line.empty()) {
                    if (line.back() == '\r') line.pop_back();
                    leakDB.insert(line);
                }
            }
            leakFile.close();
        } else {
            leakDB.insert(HashUtils::generateSHA256("123456"));
            leakDB.insert(HashUtils::generateSHA256("password"));
        }

        bool isWeak = weakPasswords.containsPattern(password);
        std::string hash = HashUtils::generateSHA256(password);
        
        // Check leak using the hash
        bool isLeaked = leakDB.isLeaked(hash);
        
        double entropy = PasswordEngine::calculateEntropy(password);
        double crackTime = PasswordEngine::calculateCrackTimeSeconds(password);

        // Format JSON output
        std::cout << "{";
        std::cout << "\"password\": \"" << password << "\", ";
        std::cout << "\"hash\": \"" << hash << "\", ";
        std::cout << "\"isWeak\": " << (isWeak ? "true" : "false") << ", ";
        std::cout << "\"isLeaked\": " << (isLeaked ? "true" : "false") << ", ";
        std::cout << "\"entropy\": " << entropy << ", ";
        std::cout << "\"crackTimeSeconds\": " << crackTime;
        std::cout << "}\n";

        return 0;
    }

    // Otherwise, start standard CLI
    CLI cli;
    cli.start();
    return 0;
}