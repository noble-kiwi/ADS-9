// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  "tree.h"

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getPermutations();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = tree.getPermutations();
    if (num < 1 || num > static_cast<int>(perms.size())) {
        return std::vector<char>();
    }
    return perms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.navigate(num);
}
