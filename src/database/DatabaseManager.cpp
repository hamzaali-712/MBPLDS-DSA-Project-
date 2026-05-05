#include "DatabaseManager.h"
#include <iostream>

bool DatabaseManager::connect() {
    std::cout << "[DB] Connected to MySQL database (Mock).\n";
    return true;
}

bool DatabaseManager::saveUser(User* user) {
    if (!user) return false;
    std::cout << "[DB] Executing: INSERT INTO users (id, username, risk) VALUES ("
              << user->getUserID() << ", '" << user->getUsername() << "', " 
              << user->getRiskLevel() << ");\n";
    return true;
}

bool DatabaseManager::updateUserPassword(int userID, const std::string& newHash) {
    std::cout << "[DB] Executing: UPDATE passwords SET hash = '" << newHash 
              << "' WHERE user_id = " << userID << ";\n";
    return true;
}

bool DatabaseManager::deleteUser(int userID) {
    std::cout << "[DB] Executing: DELETE FROM users WHERE id = " << userID << ";\n";
    return true;
}
