#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "block_with_hash_mode.h"

// Helper to generate random transactions for testing
std::vector<Transaction> generateTestTransactions(int count) {
    static int txId = 0;
    std::vector<Transaction> transactions;
    std::vector<std::string> addresses = {"Alice", "Bob", "Charlie", "Dave"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> amtDist(1, 1000);
    
    for (int i = 0; i < count; i++) {
        std::string sender = addresses[gen() % addresses.size()];
        std::string receiver;
        do {
            receiver = addresses[gen() % addresses.size()];
        } while (receiver == sender);
        
        transactions.emplace_back(
            "tx" + std::to_string(++txId),
            sender,
            receiver,
            amtDist(gen)
        );
    }
    return transactions;
}

// Test mining performance with different hash functions
void testMining(HashMode mode, int difficulty, int blockCount) {
    std::cout << "\nTesting mining with " << (mode == HashMode::AC_HASH ? "AC_HASH" : "SHA256")
              << " (difficulty " << difficulty << ")" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::vector<BlockWithHashMode> chain;
    long totalTime = 0;
    
    // Create genesis block
    chain.emplace_back(0, std::vector<Transaction>(), "0", mode);
    std::cout << "Genesis block created:" << std::endl;
    std::cout << chain[0].toString() << std::endl;
    
    // Mine subsequent blocks
    for (int i = 1; i <= blockCount; i++) {
        auto transactions = generateTestTransactions(3); // 3 transactions per block
        BlockWithHashMode block(i, transactions, chain.back().getHash(), mode);
        
        std::cout << "Mining block " << i << "..." << std::endl;
        long blockTime = block.mineBlock(difficulty);
        totalTime += blockTime;
        
        chain.push_back(block);
        std::cout << block.toString() << std::endl;
    }
    
    std::cout << "Total mining time: " << totalTime << "ms" << std::endl;
    std::cout << "Average time per block: " << (totalTime / blockCount) << "ms" << std::endl;
    
    // Verify chain integrity
    bool valid = true;
    for (size_t i = 1; i < chain.size(); i++) {
        if (chain[i].getPreviousHash() != chain[i-1].getHash()) {
            valid = false;
            std::cout << "Chain broken at block " << i << std::endl;
            break;
        }
    }
    std::cout << "Chain integrity: " << (valid ? "VALID ✓" : "INVALID ✗") << std::endl;
}

int main() {
    std::cout << "Starting blockchain tests with different hash functions..." << std::endl;
    
    // Test SHA-256 first
    testMining(HashMode::SHA256, 4, 3);  // difficulty 4, 3 blocks
    
    // Test AC_HASH
    testMining(HashMode::AC_HASH, 4, 3);  // same parameters
    
    return 0;
}