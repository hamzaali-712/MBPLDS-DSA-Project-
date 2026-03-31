#include "UserManager.h"
#include "PasswordValidation.h" // Static class with isValid()
#include <iostream>
#include <string>

int main() {
    UserManager um;

    // Default admin login
    um.addUser("MBPLDS", 0, "Pakistan@1234");

    int choice;
    std::string username, password;
    int userID;

    while (true) {
        std::cout << "\n--- MBPLDS System ---\n";
        std::cout << "1. Login\n2. Signup\n3. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        if (choice == 1) { // LOGIN
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            bool found = false;
            for (int i = 0; i < 100; i++) { // check all users
                User* u = um.searchUser(i);
                if (u && u->getUsername() == username &&
                    u->getCurrentPassword()->getValue() == password) {

                    found = true;
                    std::cout << "\nLogin successful!\n";

                    // Admin / Logged-in menu
                    int subChoice;
                    while (true) {
                        std::cout << "\n1. Add User\n2. Delete User\n3. Logout\nChoose: ";
                        std::cin >> subChoice;
                        std::cin.ignore();

                        if (subChoice == 1) { // Add new user
                            std::string newName, newPwd;
                            int newID;

                            std::cout << "New Username: ";
                            std::getline(std::cin, newName);
                            std::cout << "New UserID: ";
                            std::cin >> newID; std::cin.ignore();
                            std::cout << "New Password: ";
                            std::getline(std::cin, newPwd);

                            if (PasswordValidation::isValid(newPwd)) {
                                if (um.addUser(newName, newID, newPwd)) {
                                    std::cout << "User added successfully.\n";
                                } else {
                                    std::cout << "UserID already exists or storage full!\n";
                                }
                            } else {
                                std::cout << "Password invalid! Must be 6-50 chars, "
                                             "contain letter, digit & special $#@&\n";
                            }

                        } else if (subChoice == 2) { // Delete user
                            int delID;
                            std::cout << "UserID to delete: ";
                            std::cin >> delID; std::cin.ignore();
                            if (um.deleteUser(delID)) {
                                std::cout << "User deleted successfully.\n";
                            } else {
                                std::cout << "UserID not found!\n";
                            }

                        } else break; // Logout
                    }
                    break;
                }
            }

            if (!found) std::cout << "Invalid credentials!\n";

        } else if (choice == 2) { // SIGNUP
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "UserID: ";
            std::cin >> userID; std::cin.ignore();
            std::cout << "Password: ";
            std::getline(std::cin, password);

            if (PasswordValidation::isValid(password)) {
                if (um.addUser(username, userID, password)) {
                    std::cout << "Signup successful!\n";
                } else {
                    std::cout << "UserID already exists or storage full!\n";
                }
            } else {
                std::cout << "Password invalid! Must be 6-50 chars, "
                             "contain letter, digit & special $#@&\n";
            }

        } else break; // EXIT
    }

    std::cout << "Exiting MBPLDS. Goodbye!\n";
    return 0;
}