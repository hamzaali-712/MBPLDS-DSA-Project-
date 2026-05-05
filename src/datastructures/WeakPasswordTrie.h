#ifndef WEAKPASSWORDTRIE_H
#define WEAKPASSWORDTRIE_H

#include <string>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class WeakPasswordTrie {
private:
    TrieNode* root;

    void clear(TrieNode* node) {
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }

public:
    WeakPasswordTrie() {
        root = new TrieNode();
    }

    ~WeakPasswordTrie() {
        clear(root);
    }

    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current != nullptr && current->isEndOfWord;
    }
};

#endif
