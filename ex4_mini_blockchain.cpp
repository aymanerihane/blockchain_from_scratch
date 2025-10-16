#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "ex1_merkle_tree.h"
#include "ex2_proof_of_work.h"
#include "ex3_proof_of_stake.h"
#include "sha256.h"

// --- Transaction Class ---
class Transaction {
public:
    int id;
    std::string sender, receiver;
    double amount;
    Transaction(int i, std::string s, std::string r, double a): id(i), sender(s), receiver(r), amount(a) {}
    std::string toString() const {
        std::stringstream ss;
        ss << id << sender << receiver << amount;
        return ss.str();
    }
};

// --- Blockchain Class ---
class Blockchain {
public:
    std::vector<Block> chain;
    int difficulty;
    Blockchain(int diff): difficulty(diff) {
        chain.push_back(createGenesisBlock());
    }
    Block createGenesisBlock() {
        std::vector<Transaction> txs = {Transaction(0, "genesis", "genesis", 0)};
        std::vector<std::string> hashes;
        for(const auto& tx : txs) {
            hashes.push_back(sha256(tx.toString()));
        }
        std::string merkleRoot = buildMerkleRoot(hashes);
        Block b(0, merkleRoot, "0");
        return b;
    }
    void addBlockPoW(const std::vector<Transaction>& txs) {
        std::vector<std::string> hashes;
        for(const auto& tx : txs) {
            hashes.push_back(sha256(tx.toString()));
        }
        std::string merkleRoot = buildMerkleRoot(hashes);
        Block newBlock(chain.size(), merkleRoot, chain.back().hash);
        clock_t start = clock();
        newBlock.mineBlock(difficulty);
        clock_t end = clock();
        std::cout << "[PoW] Block mined: " << newBlock.hash << " in " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
        chain.push_back(newBlock);
    }
    void addBlockPoS(const std::vector<Transaction>& txs, const std::string& validator) {
        std::vector<std::string> hashes;
        for(const auto& tx : txs) {
            hashes.push_back(sha256(tx.toString()));
        }
        std::string merkleRoot = buildMerkleRoot(hashes);
        Block newBlock(chain.size(), merkleRoot, chain.back().hash);
        // In a real PoS, the validator would be part of the block's data to be hashed
        clock_t start = clock();
        newBlock.hash = sha256(newBlock.calculateHash() + validator);
        clock_t end = clock();
        std::cout << "[PoS] Block validated by " << validator << ": " << newBlock.hash << " in " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
        chain.push_back(newBlock);
    }
    bool isChainValid() {
        for (size_t i = 1; i < chain.size(); ++i) {
            // Recalculating the hash for validation is more complex now
            // as the original data (transactions) is not stored in the block.
            // For simplicity, we'll just check the hash pointers.
            if (chain[i].prevHash != chain[i-1].hash) return false;
        }
        return true;
    }
};

int main() {
    Blockchain bc(4); // Difficulty 4
    std::vector<Transaction> txs1 = {Transaction(1, "Alice", "Bob", 10), Transaction(2, "Bob", "Charlie", 5)};
    std::vector<Transaction> txs2 = {Transaction(3, "Charlie", "Alice", 2)};
    std::vector<Validator> validators = {{"Alice", 10}, {"Bob", 30}, {"Charlie", 60}};

    std::cout << "--- Mining with Proof of Work ---" << std::endl;
    bc.addBlockPoW(txs1);
    bc.addBlockPoW(txs2);
    std::cout << "Blockchain valid after PoW? " << (bc.isChainValid() ? "Yes" : "No") << std::endl << std::endl;

    std::cout << "--- Validating with Proof of Stake ---" << std::endl;
    std::string val1 = selectValidator(validators);
    bc.addBlockPoS(txs1, val1);
    std::string val2 = selectValidator(validators);
    bc.addBlockPoS(txs2, val2);
    std::cout << "Blockchain valid after PoS? " << (bc.isChainValid() ? "Yes" : "No") << std::endl;

    return 0;
}
