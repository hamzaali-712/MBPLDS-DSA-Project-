#include "UserManager.h"
#include <iostream>

int main() {
    UserManager um;

    // Add Users
    um.addUser("Hamza", 101, "securePass1");
    um.addUser("Ali", 102, "mypassword");

    // Display all
    std::cout << "\nAll Users:\n";
    um.displayAllUsers();

    // Search a user
    std::cout << "\nSearching UserID 101:\n";
    User* u = um.searchUser(101);
    if(u) u->display();

    // Update password
    std::cout << "\nUpdating password for UserID 101:\n";
    um.updatePassword(101, "newStrongPass");

    // Display all again
    std::cout << "\nAll Users after update:\n";
    um.displayAllUsers();

    return 0;
}