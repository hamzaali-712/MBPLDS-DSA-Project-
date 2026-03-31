#include "UserManager.h"
#include <iostream>

UserManager::UserManager() {
    userCount = 0;
    for(int i=0; i<MAX_USERS; i++) users[i] = nullptr;
}

UserManager::~UserManager() {
    for(int i=0; i<userCount; i++) {
        delete users[i];
    }
}

bool UserManager::addUser(const std::string& username, int userID, const std::string& pwd) {
    if(userCount >= MAX_USERS) {
        std::cout << "User storage full!" << std::endl;
        return false;
    }
    // Simple duplicate check
    if(searchUser(userID) != nullptr) {
        std::cout << "UserID already exists!" << std::endl;
        return false;
    }
    users[userCount++] = new User(username, userID, pwd);
    std::cout << "User added successfully." << std::endl;
    return true;
}

User* UserManager::searchUser(int userID) {
    for(int i=0; i<userCount; i++) {
        if(users[i]->getUserID() == userID) return users[i];
    }
    return nullptr;
}

bool UserManager::updatePassword(int userID, const std::string& newPwd) {
    User* user = searchUser(userID);
    if(user == nullptr) {
        std::cout << "User not found!" << std::endl;
        return false;
    }
    // Mock leak check
    if(newPwd == "123456" || newPwd == "password") {
        std::cout << "Weak or leaked password detected!" << std::endl;
        return false;
    }
    user->setPassword(newPwd);
    std::cout << "Password updated successfully." << std::endl;
    return true;
}

void UserManager::displayAllUsers() const {
    for(int i=0; i<userCount; i++) {
        users[i]->display();
        std::cout << "-----------------" << std::endl;
    }
}