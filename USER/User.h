#ifndef USER_H
#define USER_H

#include "Password.h"
#include <string>

class User {
private:
    std::string username;
    int userID;
    Password* currentPassword;
    int riskLevel;

    // Placeholders for future modules
    void* undoStack;          // Weeks 7-8
    void* passwordHistory;    // Weeks 7-8

public:
    User(const std::string& uname, int id, const std::string& pwd);
    ~User();

    // Getters
    std::string getUsername() const;
    int getUserID() const;
    Password* getCurrentPassword() const;
    int getRiskLevel() const;

    // Setters
    void setUsername(const std::string& uname);
    void setPassword(const std::string& newPwd);
    void setRiskLevel(int risk);
    
    void display() const;
};

#endif