#include "UserManager/UserManager.h"
#include <iostream>
#include <string>

int main() {
    UserManager um;
    int choice;
    
    while (true) {
        std::cout << "\n===== MBPLDS SECURITY CONSOLE =====\n1. Login\n2. Signup (New Account)\n3. Exit\nChoice: ";
        if (!(std::cin >> choice)) { 
            std::cin.clear(); 
            std::cin.ignore(1000, '\n'); 
            continue; 
        }
        std::cin.ignore();

        try {
            if (choice == 1) {
                std::string uName, uPass;
                std::cout << "Username: "; std::getline(std::cin, uName);
                std::cout << "Password: "; std::getline(std::cin, uPass);

                User* activeUser = nullptr;
                for(int i=0; i<1000; i++) {
                    User* t = um.searchUser(i);
                    if(t && t->getUsername() == uName && t->getCurrentPassword()->getValue() == uPass) {
                        activeUser = t; break;
                    }
                }

                if (activeUser) {
                    std::cout << "\n[LOGIN SUCCESSFUL]: Welcome, " << uName << "!\n";
                    while(true) {
                        std::cout << "\n--- DASHBOARD ---\n1. Add User\n2. Delete User\n3. Update My Password\n4. Undo My Password\n5. Show All Users\n6. Risk Alerts\n7. Logout\nChoice: ";
                        int sub; std::cin >> sub; std::cin.ignore();
                        try {
                            if(sub == 1) {
                                std::string n, p; int id;
                                std::cout << "Name: "; std::getline(std::cin, n);
                                std::cout << "ID: "; std::cin >> id; std::cin.ignore();
                                std::cout << "Pass: "; std::getline(std::cin, p);
                                um.addUser(n, id, p);
                            } else if(sub == 2) {
                                int id; std::cout << "Enter ID to delete: "; std::cin >> id;
                                um.deleteUser(id);
                            } else if(sub == 3) {
                                std::string p; std::cout << "New Pass: "; std::getline(std::cin, p);
                                um.updatePassword(activeUser->getUserID(), p);
                            } else if(sub == 4) {
                                activeUser->undoPassword();
                                std::cout << "[SUCCESS]: Password reverted to previous state.\n";
                            } else if(sub == 5) {
                                um.displayAllUsers();
                            } else if(sub == 6) {
                                um.showHighRiskAlert();
                            } else if(sub == 7) {
                                std::cout << "[LOGOUT]: Session ended.\n";
                                break;
                            }
                        } catch (const std::exception& e) {
                            std::cout << "\n[ERROR]: " << e.what() << "\n";
                        }
                    }
                } else {
                    std::cout << "\n[LOGIN FAILED]: Invalid credentials.\n";
                }
            } else if (choice == 2) {
                std::string n, p; int id;
                std::cout << "Full Name: "; std::getline(std::cin, n);
                std::cout << "Assign ID: "; std::cin >> id; std::cin.ignore();
                std::cout << "Set Password: "; std::getline(std::cin, p);
                um.addUser(n, id, p);
            } else if (choice == 3) {
                std::cout << "Exiting System. Goodbye!\n";
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "\n[SYSTEM ALERT]: " << e.what() << "\n";
        }
    }
    return 0;
}