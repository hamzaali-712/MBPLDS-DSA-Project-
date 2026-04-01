#include "UserManager.h"
#include "../PASSWORD/HashTable.h"
#include <iostream>
#include <cctype>

HashTable leakedDB; 

UserManager::UserManager() {
    userCount = 0;
    for(int i = 0; i < MAX_USERS; i++) users[i] = nullptr;
    leakedDB.insert("123456");
    leakedDB.insert("password");
    leakedDB.insert("admin123");
    leakedDB.insert("Pakistan@123");
    addUser("MBPLDS", 0, "Admin@123");
}

UserManager::~UserManager() {
    for(int i = 0; i < userCount; i++) {
        if(users[i]) delete users[i];
    }
}

bool UserManager::isValidPassword(const std::string& pwd) {
    // Testing ke liye sirf length check rakha hai abhi
    return (pwd.length() >= 6);
}

bool UserManager::addUser(const std::string& username, int userID, const std::string& pwd) {
    if(userCount >= MAX_USERS) return false;
    if(searchUser(userID) != nullptr) return false;
    users[userCount++] = new User(username, userID, pwd);
    return true;
}

bool UserManager::deleteUser(int userID) {
    for(int i = 0; i < userCount; i++) {
        if(users[i] && users[i]->getUserID() == userID) {
            delete users[i];
            for(int j = i; j < userCount - 1; j++) users[j] = users[j+1];
            users[--userCount] = nullptr;
            return true;
        }
    }
    return false;
}

User* UserManager::searchUser(int userID) {
    for(int i = 0; i < 2000; i++) { 
        for(int j = 0; j < userCount; j++) {
            if(users[j] && users[j]->getUserID() == userID) return users[j];
        }
    }
    return nullptr;
}

bool UserManager::updatePassword(int userID, const std::string& newPwd) {
    User* user = searchUser(userID);
    if (!user) return false;

    if (leakedDB.isLeaked(newPwd)) {
        std::cout << "\n[ALERT]: Password is LEAKED! Increasing Risk Level.\n";
        user->setRiskLevel(user->getRiskLevel() + 50); 
        return false;
    }

    if (!isValidPassword(newPwd)) {
        std::cout << "[ERROR]: Password too short (Min 6 chars).\n";
        return false;
    }

    user->setPassword(newPwd); 
    std::cout << "[SUCCESS]: Password updated to: " << newPwd << "\n";
    return true;
}

void UserManager::showHighRiskAlert() {
    riskMonitor.clear();
    bool anyRisk = false;
    for(int i = 0; i < userCount; i++) {
        if(users[i] && users[i]->getRiskLevel() > 0) {
            riskMonitor.push(users[i]);
            anyRisk = true;
        }
    }

    if (!anyRisk) {
        std::cout << "\n[STATUS]: System is Secure. Risk Level: 0\n";
    } else {
        User* top = riskMonitor.getHighestRiskUser();
        std::cout << "\n--- MAX-HEAP SECURITY REPORT ---";
        std::cout << "\nUSER: " << top->getUsername();
        std::cout << "\nRISK SCORE: " << top->getRiskLevel();
        std::cout << "\n--------------------------------\n";
    }
}

void UserManager::displayAllUsers() const {
    for(int i = 0; i < userCount; i++) {
        if(users[i]) users[i]->display();
    }
}
