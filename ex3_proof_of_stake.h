#ifndef EX3_PROOF_OF_STAKE_H
#define EX3_PROOF_OF_STAKE_H

#include <string>
#include <vector>

struct Validator {
    std::string name;
    int stake;
};

std::string selectValidator(const std::vector<Validator>& validators);

#endif // EX3_PROOF_OF_STAKE_H
