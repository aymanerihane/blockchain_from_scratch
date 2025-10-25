#ifndef EX2_PROOF_OF_WORK_H
#define EX2_PROOF_OF_WORK_H

#include <string>
#include <vector>
#include <ctime>

class Block {
public:
    int index;
    std::string data;
    std::string prevHash;
    std::string hash;
    long nonce;
    time_t timestamp;
    Block(int idx, std::string d, std::string prev);
    std::string calculateHash() const;
    void mineBlock(int difficulty);
};

#endif // EX2_PROOF_OF_WORK_H
