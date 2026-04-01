#ifndef STACK_H
#define STACK_H

#include <string>
#include <vector>

class UndoStack {
private:
    std::vector<std::string> stack;
public:
    void push(const std::string& pwd) { stack.push_back(pwd); }
    std::string pop() {
        if (stack.empty()) return "";
        std::string last = stack.back();
        stack.pop_back();
        return last;
    }
    bool isEmpty() { return stack.empty(); }
};

#endif
