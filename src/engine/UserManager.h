#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../core/User.h"
#include "../datastructures/RiskMaxHeap.h"
#include "../datastructures/UserBST.h"
#include "../datastructures/WeakPasswordTrie.h"
#include <string>

enum class MBPLDSError {
    SUCCESS = 0,
    USER_NOT_FOUND,
    USER_ALREADY_EXISTS,
    PASSWORD_REUSED,
    PASSWORD_TOO_WEAK,
    PASSWORD_LEAKED,
    NO_HISTORY,
    DB_CONNECTION_FAILED,
    INVALID_INPUT,
    MEMORY_ALLOCATION_FAILED
};

class UserManager {
private:
    UserBST userTree;
    RiskMaxHeap riskMonitor;
    WeakPasswordTrie weakPasswords;
    int userCount;

    bool isValidPassword(const std::string& pwd);

public:
    UserManager();
    ~UserManager();

    MBPLDSError addUser(const std::string& username, int userID, const std::string& pwd);
    MBPLDSError deleteUser(int userID);
    User* searchUser(int userID);
    User* searchUserByUsername(const std::string& username);
    MBPLDSError updatePassword(int userID, const std::string& newPwd);
    void displayAllUsers() const;
    void showHighRiskAlert();
};

#endif
