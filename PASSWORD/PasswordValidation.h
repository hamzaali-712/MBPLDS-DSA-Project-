#ifndef PASSWORDVALIDATION_H
#define PASSWORDVALIDATION_H

#include <string>
#include <regex>

class PasswordValidation {
public:
    static bool isValid(const std::string& pwd) {
        if (pwd.length() < 6 || pwd.length() > 50) return false;

        std::regex alpha("[A-Za-z]");
        std::regex digit("[0-9]");
        std::regex special("[$#@&]");

        if (!std::regex_search(pwd, alpha)) return false;
        if (!std::regex_search(pwd, digit)) return false;
        if (!std::regex_search(pwd, special)) return false;

        return true;
    }
};

#endif