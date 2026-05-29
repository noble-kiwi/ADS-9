// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<Node*> children;

        explicit Node(char val) : value(val) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node) {
            for (Node* child : node->children) {
                clear(child);
            }
            delete node;
        }
    }

    void build(Node* node, std::vector<char> remaining) {
        if (remaining.empty()) return;

        for (size_t i = 0; i < remaining.size(); ++i) {
            Node* child = new Node(remaining[i]);
            node->children.push_back(child);

            std::vector<char> next_remaining;
            for (size_t j = 0; j < remaining.size(); ++j) {
                if (i != j) {
                    next_remaining.push_back(remaining[j]);
                }
            }
            build(child, next_remaining);
        }
    }

    void collectPerms(Node* node, std::vector<char>& current,
                      std::vector<std::vector<char>>& result) const {
        if (!node) return;

        if (node->value != '\0') {
            current.push_back(node->value);
        }

        if (node->children.empty() && node->value != '\0') {
            result.push_back(current);
        } else {
            for (Node* child : node->children) {
                collectPerms(child, current, result);
            }
        }

        if (node->value != '\0') {
            current.pop_back();
        }
    }

    int countLeaves(Node* node) const {
        if (!node) return 0;
        if (node->children.empty()) return 1;
        int count = 0;
        for (Node* child : node->children) {
            count += countLeaves(child);
        }
        return count;
    }

 public:
    explicit PMTree(const std::vector<char>& elements) {
        root = new Node('\0');
        build(root, elements);
    }

    ~PMTree() {
        clear(root);
    }

    std::vector<std::vector<char>> getPermutations() const {
        std::vector<std::vector<char>> result;
        std::vector<char> current;
        collectPerms(root, current, result);
        return result;
    }

    std::vector<char> navigate(int num) const {
        std::vector<char> result;
        Node* current = root;
        int target = num - 1;

        if (target < 0 || target >= countLeaves(root)) {
            return std::vector<char>();
        }

        while (!current->children.empty()) {
            int subtree_leaves = countLeaves(current->children[0]);
            int index = target / subtree_leaves;
            target %= subtree_leaves;

            current = current->children[index];
            result.push_back(current->value);
        }

        return result;
    }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
