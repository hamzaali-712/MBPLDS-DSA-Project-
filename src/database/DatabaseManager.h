#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "../core/User.h"
#include <string>

class DatabaseManager {
public:
    static bool connect();
    static bool saveUser(User* user);
    static bool updateUserPassword(int userID, const std::string& newHash);
    static bool deleteUser(int userID);
};

#endif
