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

    // Check if the password contains any of the weak passwords as a substring
    bool containsPattern(const std::string& word) {
        std::string lowerWord = word;
        for (char& c : lowerWord) c = std::tolower(c);

        for (size_t i = 0; i < lowerWord.length(); ++i) {
            TrieNode* current = root;
            for (size_t j = i; j < lowerWord.length(); ++j) {
                char ch = lowerWord[j];
                if (current->children.find(ch) == current->children.end()) {
                    break;
                }
                current = current->children[ch];
                if (current->isEndOfWord) {
                    return true;
                }
            }
        }
        return false;
    }
};

#endif
