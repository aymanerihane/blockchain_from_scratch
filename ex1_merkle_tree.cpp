// Basic Merkle Tree for transaction hashes
#include <iostream>
#include <vector>
#include <string>
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

class MerkleTree {
public:
    std::string root;
    MerkleTree(const std::vector<std::string>& leaves) {
        root = buildTree(leaves);
    }
    static std::string buildTree(std::vector<std::string> leaves) {
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
};

int main() {
    std::vector<std::string> txs = {"tx1", "tx2", "tx3", "tx4"};
    std::vector<std::string> hashes;
    for (const auto& tx : txs) hashes.push_back(sha256(tx));
    MerkleTree tree(hashes);
    std::cout << "Merkle Root: " << tree.root << std::endl;
    return 0;
}
