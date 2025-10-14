#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    char outputBuffer[65];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    outputBuffer[64] = 0;
    return std::string(outputBuffer);
}

class Block {
public:
    int index;
    std::string data;
    std::string prevHash;
    std::string hash;
    long nonce;
    time_t timestamp;
    Block(int idx, std::string d, std::string prev): index(idx), data(d), prevHash(prev), nonce(0) {
        timestamp = std::time(nullptr);
        hash = calculateHash();
    }
    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << data << prevHash << timestamp << nonce;
        return sha256(ss.str());
    }
    void mineBlock(int difficulty) {
        std::string prefix(difficulty, '0');
        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, difficulty) != prefix);
    }
};

int main() {
    int difficulty = 4;
    Block b(1, "Test Block", "0");
    std::cout << "Mining block with difficulty " << difficulty << "...\n";
    clock_t start = clock();
    b.mineBlock(difficulty);
    clock_t end = clock();
    std::cout << "Block mined: " << b.hash << std::endl;
    std::cout << "Time taken: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}
