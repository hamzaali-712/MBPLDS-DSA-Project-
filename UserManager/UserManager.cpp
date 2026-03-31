#include "UserManager.h"
#include <iostream>
#include <cctype>

UserManager::UserManager() {
    userCount = 0;
    for(int i = 0; i < MAX_USERS; i++) users[i] = nullptr;

    // Default user
    addUser("MBPLDS", 1, "Pakistan@1234");
}

UserManager::~UserManager() {
    for(int i = 0; i < userCount; i++) {
        delete users[i];
    }
}

// Password validation: 6-50 chars, 1 alphabet, 1 digit, 1 special char ($#@&)
bool UserManager::isValidPassword(const std::string& pwd) {
    if(pwd.length() < 6 || pwd.length() > 50) return false;

    bool hasAlpha = false, hasDigit = false, hasSpecial = false;
    for(char ch : pwd) {
        if(isalpha(ch)) hasAlpha = true;
        else if(isdigit(ch)) hasDigit = true;
        else if(ch == '$' || ch == '#' || ch == '@' || ch == '&') hasSpecial = true;
    }
    return hasAlpha && hasDigit && hasSpecial;
}

bool UserManager::addUser(const std::string& username, int userID, const std::string& pwd) {
    if(userCount >= MAX_USERS) {
        std::cout << "User storage full!\n";
        return false;
    }

    if(searchUser(userID) != nullptr) {
        std::cout << "UserID already exists!\n";
        return false;
    }

    if(!isValidPassword(pwd)) {
        std::cout << "Password does not meet the requirements!\n";
        return false;
    }

    users[userCount++] = new User(username, userID, pwd);
    std::cout << "User added successfully.\n";
    return true;
}

bool UserManager::deleteUser(int userID) {
    for(int i = 0; i < userCount; i++) {
        if(users[i]->getUserID() == userID) {
            delete users[i];
            for(int j = i; j < userCount - 1; j++) users[j] = users[j+1];
            users[--userCount] = nullptr;
            std::cout << "User deleted successfully.\n";
            return true;
        }
    }
    std::cout << "User not found!\n";
    return false;
}

User* UserManager::searchUser(int userID) {
    for(int i = 0; i < userCount; i++) {
        if(users[i]->getUserID() == userID) return users[i];
    }
    return nullptr;
}

bool UserManager::updatePassword(int userID, const std::string& newPwd) {
    User* user = searchUser(userID);
    if(user == nullptr) {
        std::cout << "User not found!\n";
        return false;
    }

    if(!isValidPassword(newPwd)) {
        std::cout << "Password does not meet the requirements!\n";
        return false;
    }

    user->setPassword(newPwd);
    std::cout << "Password updated successfully.\n";
    return true;
}

void UserManager::displayAllUsers() const {
    for(int i = 0; i < userCount; i++) {
        users[i]->display();
        std::cout << "-----------------\n";
    }
}