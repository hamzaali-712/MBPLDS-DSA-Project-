#ifndef USERBST_H
#define USERBST_H

#include "../core/User.h"
#include <string>
#include <iostream>

class BSTNode {
public:
    User* user;
    BSTNode* left;
    BSTNode* right;

    BSTNode(User* u) : user(u), left(nullptr), right(nullptr) {}
};

class UserBST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, User* user) {
        if (!node) return new BSTNode(user);
        
        if (user->getUserID() < node->user->getUserID()) {
            node->left = insertRec(node->left, user);
        } else if (user->getUserID() > node->user->getUserID()) {
            node->right = insertRec(node->right, user);
        }
        return node;
    }

    User* searchRec(BSTNode* node, int id) const {
        if (!node || node->user->getUserID() == id) {
            return node ? node->user : nullptr;
        }
        if (id < node->user->getUserID()) {
            return searchRec(node->left, id);
        }
        return searchRec(node->right, id);
    }

    User* searchRecByUsername(BSTNode* node, const std::string& username) const {
        if (!node) return nullptr;
        if (node->user->getUsername() == username) return node->user;
        User* leftSearch = searchRecByUsername(node->left, username);
        if (leftSearch) return leftSearch;
        return searchRecByUsername(node->right, username);
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    BSTNode* removeRec(BSTNode* node, int id) {
        if (!node) return node;

        if (id < node->user->getUserID()) {
            node->left = removeRec(node->left, id);
        } else if (id > node->user->getUserID()) {
            node->right = removeRec(node->right, id);
        } else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = minValueNode(node->right);
            node->user = temp->user;
            node->right = removeRec(node->right, temp->user->getUserID());
        }
        return node;
    }

    void inOrderRec(BSTNode* node) const {
        if (node) {
            inOrderRec(node->left);
            node->user->display();
            inOrderRec(node->right);
        }
    }

public:
    UserBST() : root(nullptr) {}

    void insert(User* user) {
        root = insertRec(root, user);
    }

    User* search(int id) const {
        return searchRec(root, id);
    }

    User* searchByUsername(const std::string& username) const {
        return searchRecByUsername(root, username);
    }

    void remove(int id) {
        root = removeRec(root, id);
    }

    void displayAll() const {
        inOrderRec(root);
    }
};

#endif
