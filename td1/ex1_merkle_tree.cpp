#include "ex1_merkle_tree.h"
#include "sha256.h"
#include <iostream>

std::string buildMerkleRoot(const std::vector<std::string>& leaves) {
    if (leaves.empty()) return "";
    if (leaves.size() == 1) return leaves[0];

    std::vector<std::string> current_level = leaves;
    while (current_level.size() > 1) {
        if (current_level.size() % 2 != 0) {
            current_level.push_back(current_level.back());
        }
        std::vector<std::string> next_level;
        for (size_t i = 0; i < current_level.size(); i += 2) {
            next_level.push_back(sha256(current_level[i] + current_level[i+1]));
        }
        current_level = next_level;
    }
    return current_level[0];
}


