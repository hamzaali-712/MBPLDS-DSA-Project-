#ifndef RISKQUEUE_H
#define RISKQUEUE_H

#include "../USER/User.h"
#include <vector>
#include <algorithm>

class RiskQueue {
private:
    std::vector<User*> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index]->getRiskLevel() > heap[parent]->getRiskLevel()) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

public:
    void push(User* user) {
        if (!user) return;
        heap.push_back(user);
        heapifyUp(heap.size() - 1);
    }

    User* getHighestRiskUser() {
        if (heap.empty()) return nullptr;
        return heap[0];
    }

    void clear() { heap.clear(); }
    bool isEmpty() { return heap.empty(); }
};

#endif
