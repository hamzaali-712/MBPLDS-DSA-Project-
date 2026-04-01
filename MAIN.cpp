#include "UserManager/UserManager.h"
#include <iostream>
#include <string>

int main() {
    UserManager um;
    int choice;
    std::string username, password;

    while (true) {
        std::cout << "\n--- MBPLDS Security Console ---\n";
        std::cout << "1. Login\n2. Signup\n3. Exit\nChoose: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice == 1) { 
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            User* u = nullptr;
            for (int i = 0; i < 1000; i++) { 
                User* temp = um.searchUser(i);
                if (temp && temp->getUsername() == username && temp->getCurrentPassword()->getValue() == password) {
                    u = temp;
                    break;
                }
            }

            if (u) {
                std::cout << "\nLogin Successful! Welcome, " << username << "\n";
                int sub;
                while (true) {
                    std::cout << "\n--- User Dashboard ---\n1. Add User\n2. Delete User\n3. Undo Password\n4. Update Password\n5. Risk Alerts\n6. Logout\nChoose: ";
                    if (!(std::cin >> sub)) { std::cin.clear(); std::cin.ignore(1000, '\n'); continue; }
                    std::cin.ignore();

                    if (sub == 1) {
                        std::string n, p; int id;
                        std::cout << "Name: "; std::getline(std::cin, n);
                        std::cout << "ID: "; std::cin >> id; std::cin.ignore();
                        std::cout << "Pass: "; std::getline(std::cin, p);
                        um.addUser(n, id, p);
                    } else if (sub == 2) {
                        int id; std::cout << "ID: "; std::cin >> id; std::cin.ignore();
                        um.deleteUser(id);
                    } else if (sub == 3) {
                        u->undoPassword();
                    } else if (sub == 4) {
                        std::string p; std::cout << "New Pass: "; std::getline(std::cin, p);
                        um.updatePassword(u->getUserID(), p);
                    } else if (sub == 5) {
                        um.showHighRiskAlert();
                    } else if (sub == 6) break;
                }
            } else std::cout << "Invalid Login!\n";
        } else if (choice == 2) {
            std::string n, p; int id;
            std::cout << "Name: "; std::getline(std::cin, n);
            std::cout << "ID: "; std::cin >> id; std::cin.ignore();
            std::cout << "Pass: "; std::getline(std::cin, p);
            um.addUser(n, id, p);
        } else if (choice == 3) break;
    }
    return 0;
}