#include "ex2_proof_of_work.h"
#include "sha256.h"
#include <iostream>
#include <sstream>

Block::Block(int idx, std::string d, std::string prev): index(idx), data(d), prevHash(prev), nonce(0) {
    timestamp = std::time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << data << prevHash << timestamp << nonce;
    return sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string prefix(difficulty, '0');
    do {
        nonce++;
        hash = calculateHash();
    } while (hash.substr(0, difficulty) != prefix);
}


