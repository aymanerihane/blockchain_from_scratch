#include "ex3_proof_of_stake.h"
#include <iostream>
#include <random>
#include <ctime>

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


