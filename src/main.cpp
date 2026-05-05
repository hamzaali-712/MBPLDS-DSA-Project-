#include "ui/CLI.h"
#include "engine/PasswordEngine.h"
#include "datastructures/WeakPasswordTrie.h"
#include "datastructures/LeakHashTable.h"
#include "engine/HashUtils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Check if running in API mode for Streamlit
    if (argc == 3 && std::string(argv[1]) == "--analyze") {
        std::string password = argv[2];
        
        // Setup mock DBs quickly for analysis
        WeakPasswordTrie weakPasswords;
        weakPasswords.insert("password");
        weakPasswords.insert("admin");
        weakPasswords.insert("qwerty");
        weakPasswords.insert("123456");

        LeakHashTable leakDB;
        leakDB.insert("123456");
        leakDB.insert("password");

        bool isWeak = weakPasswords.search(password);
        std::string hash = HashUtils::generateSHA256(password);
        
        // Mock leak check (using raw string since mock DB was seeded with raw strings)
        bool isLeaked = leakDB.isLeaked(password); 
        
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