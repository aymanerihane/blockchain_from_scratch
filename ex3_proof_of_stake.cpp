#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>

struct Validator {
    std::string name;
    int stake;
};

std::string selectValidator(const std::vector<Validator>& validators) {
    int totalStake = 0;
    for (const auto& v : validators) totalStake += v.stake;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, totalStake);
    int r = dis(gen);
    int sum = 0;
    for (const auto& v : validators) {
        sum += v.stake;
        if (r <= sum) return v.name;
    }
    return validators.back().name;
}

int main() {
    std::vector<Validator> validators = {
        {"Alice", 10},
        {"Bob", 30},
        {"Charlie", 60}
    };
    std::cout << "Selecting validator (PoS)...\n";
    clock_t start = clock();
    std::string winner = selectValidator(validators);
    clock_t end = clock();
    std::cout << "Selected validator: " << winner << std::endl;
    std::cout << "Time taken: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}
