#ifndef USER_H
#define USER_H

#include "../PASSWORD/Password.h"
#include "../PASSWORD/Stack.h"
#include <string>
#include <vector>

// Doubly Linked List Node for Password History
struct PasswordNode {
    std::string pwdValue;
    PasswordNode* next;
    PasswordNode* prev;
    PasswordNode(std::string v) : pwdValue(v), next(nullptr), prev(nullptr) {}
};

class User {
private:
    std::string username;
    int userID;
    Password* currentPassword;
    int riskLevel;

    // Farukh's Modules (Replacing void* with actual structures)
    UndoStack* undoStack;          // For $O(1)$ Undo operations
    PasswordNode* historyHead;     // Head of Doubly Linked List for history
    PasswordNode* historyTail;     // Tail for quick access

public:
    User(const std::string& uname, int id, const std::string& pwd);
    ~User();

    // Getters
    std::string getUsername() const;
    int getUserID() const;
    Password* getCurrentPassword() const;
    int getRiskLevel() const;

    // Setters & Logic
    void setUsername(const std::string& uname);
    void setPassword(const std::string& newPwd); // This will handle Stack push
    void setRiskLevel(int risk);
    
    // Farukh's Security Functions
    void undoPassword(); // Pop from stack and restore
    void addToHistory(const std::string& oldPwd);
    
    void display() const;
};

#endif