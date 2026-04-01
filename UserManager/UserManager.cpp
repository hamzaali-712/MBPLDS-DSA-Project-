#include "UserManager.h"
#include "../PASSWORD/HashTable.h"
#include <iostream>
#include <cctype>
#include <stdexcept>

HashTable leakedDB; 

UserManager::UserManager() {
    userCount = 0;
    for(int i = 0; i < MAX_USERS; i++) users[i] = nullptr;
    
    leakedDB.insert("123456");
    leakedDB.insert("password");
    leakedDB.insert("admin123");
    leakedDB.insert("Pakistan@123");

    users[userCount++] = new User("Admin_Farukh", 0, "Admin786!"); 
}

UserManager::~UserManager() {
    for(int i = 0; i < userCount; i++) if(users[i]) delete users[i];
}

bool UserManager::isValidPassword(const std::string& pwd) {
    if(pwd.length() < 6) return false;
    bool alpha = false, digit = false, special = false;
    for(char ch : pwd) {
        if(isalpha(ch)) alpha = true;
        else if(isdigit(ch)) digit = true;
        else if(ispunct(ch)) special = true;
    }
    return alpha && digit && special;
}

bool UserManager::addUser(const std::string& username, int userID, const std::string& pwd) {
    if(searchUser(userID) != nullptr) {
        throw std::runtime_error("ID EXISTS: User ID " + std::to_string(userID) + " is already taken.");
    }

    if (leakedDB.isLeaked(pwd)) {
        throw std::invalid_argument("PROACTIVE BLOCK: This password is in LEAKED database. User not created.");
    }

    if(!isValidPassword(pwd)) {
        throw std::invalid_argument("WEAK PASSWORD: Need 6+ chars, Letter, Number & Special Char.");
    }

    if(userCount >= MAX_USERS) throw std::runtime_error("SYSTEM FULL.");

    users[userCount++] = new User(username, userID, pwd);
    std::cout << "\n[SUCCESS]: User '" << username << "' added successfully!\n";
    return true;
}

bool UserManager::deleteUser(int userID) {
    if (userID == 0) {
        throw std::runtime_error("ACCESS DENIED: Root Admin (ID 0) cannot be deleted.");
    }

    for(int i = 0; i < userCount; i++) {
        if(users[i] && users[i]->getUserID() == userID) {
            std::string name = users[i]->getUsername();
            delete users[i];
            for(int j = i; j < userCount - 1; j++) users[j] = users[j+1];
            users[--userCount] = nullptr;
            std::cout << "\n[SUCCESS]: User '" << name << "' deleted.\n";
            return true;
        }
    }
    throw std::runtime_error("USER NOT FOUND: Cannot delete.");
}

bool UserManager::updatePassword(int userID, const std::string& newPwd) {
    User* user = searchUser(userID);
    if (!user) throw std::runtime_error("USER NOT FOUND.");

    if (leakedDB.isLeaked(newPwd)) {
        user->setRiskLevel(user->getRiskLevel() + 50);
        throw std::invalid_argument("SECURITY ALERT: Password is LEAKED! Risk score increased.");
    }

    if (!isValidPassword(newPwd)) {
        throw std::invalid_argument("UPDATE FAILED: New password is too weak (Min 6 chars + Complexity).");
    }

    user->setPassword(newPwd);
    std::cout << "\n[SUCCESS]: Password updated successfully!\n";
    return true;
}

User* UserManager::searchUser(int userID) {
    for(int i = 0; i < userCount; i++) {
        if(users[i] && users[i]->getUserID() == userID) return users[i];
    }
    return nullptr;
}

void UserManager::displayAllUsers() const {
    if(userCount == 0) { std::cout << "No users.\n"; return; }
    std::cout << "\n--- REGISTERED USERS DIRECTORY ---\n";
    for(int i = 0; i < userCount; i++) {
        if(users[i]) users[i]->display();
    }
}

void UserManager::showHighRiskAlert() {
    riskMonitor.clear();
    bool found = false;
    for(int i = 0; i < userCount; i++) {
        if(users[i] && users[i]->getRiskLevel() > 0) {
            riskMonitor.push(users[i]);
            found = true;
        }
    }
    if(!found) std::cout << "\n[STATUS]: System Secure. No high-risk threats detected.\n";
    else {
        User* top = riskMonitor.getHighestRiskUser();
        std::cout << "\n!!! SECURITY ALERT: HIGH RISK USER DETECTED !!!";
        std::cout << "\nUsername: " << top->getUsername() << " (ID: " << top->getUserID() << ")";
        std::cout << "\nRisk Score: " << top->getRiskLevel() << "\n";
    }}