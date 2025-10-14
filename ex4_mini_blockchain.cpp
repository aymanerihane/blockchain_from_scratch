#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <random>
#include <openssl/evp.h>
#include <openssl/sha.h>

// --- SHA256 Hashing using OpenSSL 3.0 EVP API ---
std::string sha256(const std::string& str) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned int hash_len;

    md = EVP_get_digestbyname("sha256");
    if (md == NULL) {
        std::cerr << "Error: sha256 digest not found." << std::endl;
        return "";
    }

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        std::cerr << "Error: EVP_MD_CTX_new failed." << std::endl;
        return "";
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        std::cerr << "Error: EVP_DigestInit_ex failed." << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    if (1 != EVP_DigestUpdate(mdctx, str.c_str(), str.size())) {
        std::cerr << "Error: EVP_DigestUpdate failed." << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        std::cerr << "Error: EVP_DigestFinal_ex failed." << std::endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < hash_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// --- Transaction Class (from ex4) ---
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

// --- Merkle Tree (from ex1) ---
std::string buildMerkleRoot(std::vector<std::string> leaves) {
    if (leaves.empty()) return "";
    while (leaves.size() > 1) {
        if (leaves.size() % 2 != 0) leaves.push_back(leaves.back());
        std::vector<std::string> newLevel;
        for (size_t i = 0; i < leaves.size(); i += 2) {
            newLevel.push_back(sha256(leaves[i] + leaves[i+1]));
        }
        leaves = newLevel;
    }
    return leaves[0];
}

// --- Block Class (incorporating ex2) ---
class Block {
public:
    int index;
    std::vector<Transaction> transactions;
    std::string prevHash;
    std::string merkleRoot;
    std::string hash;
    long nonce;
    time_t timestamp;
    std::string validator; // For PoS

    Block(int idx, std::vector<Transaction> txs, std::string prev): index(idx), transactions(txs), prevHash(prev), nonce(0), validator("") {
        timestamp = std::time(nullptr);
        std::vector<std::string> hashes;
        for (const auto& tx : transactions) hashes.push_back(sha256(tx.toString()));
        merkleRoot = buildMerkleRoot(hashes);
        hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << merkleRoot << prevHash << timestamp << nonce << validator;
        return sha256(ss.str());
    }

    // Proof of Work (from ex2)
    void mineBlock(int difficulty) {
        std::string prefix(difficulty, '0');
        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, difficulty) != prefix);
    }

    // Proof of Stake validation
    void validateByPoS(const std::string& val) {
        validator = val;
        hash = calculateHash();
    }
};

// --- Blockchain Class (from ex4) ---
class Blockchain {
public:
    std::vector<Block> chain;
    int difficulty;
    Blockchain(int diff): difficulty(diff) {
        chain.push_back(createGenesisBlock());
    }
    Block createGenesisBlock() {
        std::vector<Transaction> txs = {Transaction(0, "genesis", "genesis", 0)};
        return Block(0, txs, "0");
    }
    void addBlockPoW(const std::vector<Transaction>& txs) {
        Block newBlock(chain.size(), txs, chain.back().hash);
        clock_t start = clock();
        newBlock.mineBlock(difficulty);
        clock_t end = clock();
        std::cout << "[PoW] Block mined: " << newBlock.hash << " in " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
        chain.push_back(newBlock);
    }
    void addBlockPoS(const std::vector<Transaction>& txs, const std::string& validator) {
        Block newBlock(chain.size(), txs, chain.back().hash);
        clock_t start = clock();
        newBlock.validateByPoS(validator);
        clock_t end = clock();
        std::cout << "[PoS] Block validated by " << validator << ": " << newBlock.hash << " in " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
        chain.push_back(newBlock);
    }
    bool isChainValid() {
        for (size_t i = 1; i < chain.size(); ++i) {
            if (chain[i].hash != chain[i].calculateHash()) return false;
            if (chain[i].prevHash != chain[i-1].hash) return false;
        }
        return true;
    }
};

// --- PoS Validator Selection (from ex3) ---
struct Validator {
    std::string name;
    int stake;
};
std::string selectValidator(const std::vector<Validator>& validators) {
    int totalStake = 0;
    for (const auto& v : validators) totalStake += v.stake;
    if (totalStake == 0) return ""; // Avoid division by zero
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, totalStake);
    int r = dis(gen);
    int sum = 0;
    for (const auto& v : validators) {
        sum += v.stake;
        if (r <= sum) return v.name;
    }
    return validators.back().name; // Should not be reached if totalStake > 0
}

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
