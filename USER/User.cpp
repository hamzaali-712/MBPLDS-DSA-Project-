#include "User.h"
#include <iostream>

User::User(const std::string& uname, int id, const std::string& pwd) {
    username = uname;
    userID = id;
    currentPassword = new Password(pwd);
    riskLevel = 0;
    
    // Initialize Farukh's modules
    undoStack = new UndoStack();
    historyHead = nullptr;
    historyTail = nullptr;
}

User::~User() {
    delete currentPassword;
    delete undoStack;
    
    // Clean up history Linked List
    PasswordNode* curr = historyHead;
    while (curr) {
        PasswordNode* next = curr->next;
        delete curr;
        curr = next;
    }
}

std::string User::getUsername() const { return username; }
int User::getUserID() const { return userID; }
Password* User::getCurrentPassword() const { return currentPassword; }
int User::getRiskLevel() const { return riskLevel; }

void User::setUsername(const std::string& uname) { username = uname; }

void User::setPassword(const std::string& newPwd) {
    // 1. Current password ko stack mein push karo (Before updating)
    undoStack->push(currentPassword->getValue());
    
    // 2. History (DLL) mein add karo
    addToHistory(currentPassword->getValue());

    // 3. Update current password
    delete currentPassword;
    currentPassword = new Password(newPwd);
}

void User::setRiskLevel(int risk) { riskLevel = risk; }

void User::undoPassword() {
    std::string oldPwd = undoStack->pop();
    if (!oldPwd.empty()) {
        delete currentPassword;
        currentPassword = new Password(oldPwd);
        std::cout << "Undo successful! Restored previous password.\n";
    } else {
        std::cout << "No more passwords in undo history.\n";
    }
}

void User::addToHistory(const std::string& oldPwd) {
    PasswordNode* newNode = new PasswordNode(oldPwd);
    if (!historyHead) {
        historyHead = historyTail = newNode;
    } else {
        historyTail->next = newNode;
        newNode->prev = historyTail;
        historyTail = newNode;
    }
}

void User::display() const {
    std::cout << "UserID: " << userID << ", Username: " << username 
              << ", RiskLevel: " << riskLevel << std::endl;
    currentPassword->display();
}