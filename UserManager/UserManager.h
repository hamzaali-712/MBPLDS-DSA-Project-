#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <string>

#define MAX_USERS 100

class UserManager {
private:
    User* users[MAX_USERS];
    int userCount;

public:
    UserManager();
    ~UserManager();

    bool addUser(const std::string& username, int userID, const std::string& pwd);
    User* searchUser(int userID);
    bool updatePassword(int userID, const std::string& newPwd);
    void displayAllUsers() const;
};

#endif