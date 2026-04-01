#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "RiskQueue.h"
#include <string>

#define MAX_USERS 100

class UserManager {
private:
    User* users[MAX_USERS];
    int userCount;
    RiskQueue riskMonitor;

    bool isValidPassword(const std::string& pwd);

public:
    UserManager();
    ~UserManager();

    bool addUser(const std::string& username, int userID, const std::string& pwd);
    bool deleteUser(int userID);
    User* searchUser(int userID);
    bool updatePassword(int userID, const std::string& newPwd);
    void displayAllUsers() const;
    void showHighRiskAlert();
};

#endif
