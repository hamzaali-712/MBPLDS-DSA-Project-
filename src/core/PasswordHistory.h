#ifndef PASSWORDHISTORY_H
#define PASSWORDHISTORY_H

#include <string>
#include <deque>

#define MAX_HISTORY 10

class PasswordHistoryStack {
private:
    std::deque<std::string> stack;
public:
    void push(const std::string& pwd) { 
        stack.push_back(pwd); 
        if (stack.size() > MAX_HISTORY) {
            stack.pop_front();
        }
    }
    std::string pop() {
        if (stack.empty()) return "";
        std::string last = stack.back();
        stack.pop_back();
        return last;
    }
    bool isEmpty() { return stack.empty(); }
    int size() { return stack.size(); }
};

#endif
