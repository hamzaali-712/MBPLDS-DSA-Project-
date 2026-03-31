#include "User.h"
#include <iostream>

User::User(const std::string& uname, int id, const std::string& pwd) {
    username = uname;
    userID = id;
    currentPassword = new Password(pwd);
    riskLevel = 0;
    undoStack = nullptr;
    passwordHistory = nullptr;
}

User::~User() {
    delete currentPassword;
}

std::string User::getUsername() const { return username; }
int User::getUserID() const { return userID; }
Password* User::getCurrentPassword() const { return currentPassword; }
int User::getRiskLevel() const { return riskLevel; }

void User::setUsername(const std::string& uname) { username = uname; }
void User::setPassword(const std::string& newPwd) {
    delete currentPassword;
    currentPassword = new Password(newPwd);
}
void User::setRiskLevel(int risk) { riskLevel = risk; }

void User::display() const {
    std::cout << "UserID: " << userID << ", Username: " << username 
              << ", RiskLevel: " << riskLevel << std::endl;
    currentPassword->display();
}