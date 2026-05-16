#include "UserManager.h"
#include "PasswordEngine.h"
#include "../datastructures/LeakHashTable.h"
#include "../database/DatabaseManager.h"
#include <iostream>
#include <cctype>
#include <exception>

// Global mock databases for simplicity in this project
LeakHashTable leakedDB;

UserManager::UserManager() {
    userCount = 0;
    // Simulate loading weak passwords and leaked hashes
    leakedDB.insert("123456");
    leakedDB.insert("password");
    leakedDB.insert("admin");
    
    weakPasswords.insert("password");
    weakPasswords.insert("admin");
    weakPasswords.insert("qwerty");
    
    DatabaseManager::connect();
    
    addUser("MBPLDS", 0, "Admin@123");
}

UserManager::~UserManager() {
}

bool UserManager::isValidPassword(const std::string& pwd) {
    return PasswordEngine::meetsComplexityRequirements(pwd);
}

MBPLDSError UserManager::addUser(const std::string& username, int userID, const std::string& pwd) {
    try {
        if (!isValidPassword(pwd)) {
            std::cout << "[ERROR]: Invalid password format.\n";
            return MBPLDSError::INVALID_INPUT;
        }

        if (userTree.search(userID) != nullptr) {
            std::cout << "[ERROR]: User ID already exists.\n";
            return MBPLDSError::USER_ALREADY_EXISTS;
        }
        
        if (weakPasswords.search(pwd)) {
            std::cout << "[ERROR]: Password is too weak (found in weak list).\n";
            return MBPLDSError::PASSWORD_TOO_WEAK;
        }
        
        User* newUser = new User(username, userID, pwd);
        if (!newUser) return MBPLDSError::MEMORY_ALLOCATION_FAILED;

        userTree.insert(newUser);
        userCount++;
        DatabaseManager::saveUser(newUser);
        std::cout << "[SUCCESS]: User added successfully.\n";
        return MBPLDSError::SUCCESS;
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory error: " << e.what() << "\n";
        return MBPLDSError::MEMORY_ALLOCATION_FAILED;
    } catch (const std::exception& e) {
        std::cerr << "System error: " << e.what() << "\n";
        return MBPLDSError::INVALID_INPUT;
    }
}

MBPLDSError UserManager::deleteUser(int userID) {
    User* user = userTree.search(userID);
    if (!user) {
        std::cout << "[ERROR]: User not found.\n";
        return MBPLDSError::USER_NOT_FOUND;
    }
    
    userTree.remove(userID);
    userCount--;
    DatabaseManager::deleteUser(userID);
    std::cout << "[SUCCESS]: User deleted.\n";
    return MBPLDSError::SUCCESS;
}

User* UserManager::searchUser(int userID) {
    return userTree.search(userID);
}

User* UserManager::searchUserByUsername(const std::string& username) {
    return userTree.searchByUsername(username);
}

MBPLDSError UserManager::updatePassword(int userID, const std::string& newPwd) {
    User* user = userTree.search(userID);
    if (!user) {
        std::cout << "[ERROR]: User not found.\n";
        return MBPLDSError::USER_NOT_FOUND;
    }

    if (!isValidPassword(newPwd)) {
        std::cout << "[ERROR]: Invalid password format.\n";
        return MBPLDSError::INVALID_INPUT;
    }
    
    if (weakPasswords.search(newPwd)) {
        std::cout << "[ERROR]: Password is too weak (found in weak list).\n";
        return MBPLDSError::PASSWORD_TOO_WEAK;
    }
    
    user->setPassword(newPwd); 
    DatabaseManager::updateUserPassword(userID, user->getCurrentPassword()->getHash());
    std::cout << "[SUCCESS]: Password updated to: " << newPwd << "\n";
    return MBPLDSError::SUCCESS;
}

void UserManager::displayAllUsers() const {
    userTree.displayAll();
}

void UserManager::showHighRiskAlert() {
    std::cout << "[INFO]: Displaying high risk users from Risk Max-Heap...\n";
}
