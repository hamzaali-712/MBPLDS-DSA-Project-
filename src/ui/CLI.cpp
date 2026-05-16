#include "CLI.h"
#include <iostream>
#include <string>

void CLI::start() {
    int choice;
    std::string username, password;

    while (true) {
        std::cout << "\n--- MBPLDS Admin Security Console ---\n";
        std::cout << "1. Login as Admin\n2. Exit\nChoose: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice == 1) { 
            std::cout << "Username (try MBPLDS): ";
            std::getline(std::cin, username);
            std::cout << "Password (try Admin@123): ";
            std::getline(std::cin, password);

            User* u = um.searchUserByUsername(username);
            if (u && u->getCurrentPassword()->getValue() == password) {
                std::cout << "\nLogin Successful! Welcome, " << username << "\n";
                int sub;
                while (true) {
                    std::cout << "\n--- Dashboard ---\n"
                              << "1. Add User (Step 1)\n"
                              << "2. Delete User\n"
                              << "3. Update User Password (Step 9)\n"
                              << "4. Undo Password Change (Step 10)\n"
                              << "5. View High Risk Alerts (Step 8)\n"
                              << "6. View All Users\n"
                              << "7. Logout\nChoose: ";
                    if (!(std::cin >> sub)) { std::cin.clear(); std::cin.ignore(1000, '\n'); continue; }
                    std::cin.ignore();

                    if (sub == 1) {
                        std::string n, p; int id;
                        std::cout << "New Username: "; std::getline(std::cin, n);
                        std::cout << "User ID: "; std::cin >> id; std::cin.ignore();
                        std::cout << "Initial Password: "; std::getline(std::cin, p);
                        um.addUser(n, id, p);
                    } else if (sub == 2) {
                        int id; std::cout << "User ID: "; std::cin >> id; std::cin.ignore();
                        um.deleteUser(id);
                    } else if (sub == 3) {
                        int id; std::cout << "User ID: "; std::cin >> id; std::cin.ignore();
                        std::string p; std::cout << "New Password: "; std::getline(std::cin, p);
                        um.updatePassword(id, p);
                    } else if (sub == 4) {
                        int id; std::cout << "User ID: "; std::cin >> id; std::cin.ignore();
                        User* target = um.searchUser(id);
                        if(target) target->undoPassword();
                        else std::cout << "[ERROR]: User not found.\n";
                    } else if (sub == 5) {
                        um.showHighRiskAlert();
                    } else if (sub == 6) {
                        um.displayAllUsers();
                    } else if (sub == 7) break;
                }
            } else {
                std::cout << "[ERROR]: Invalid Admin Login!\n";
            }
        } else if (choice == 2) {
            break;
        }
    }
}
