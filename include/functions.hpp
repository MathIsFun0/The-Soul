#include <string>
#include <algorithm>
#include "instance.hpp"
// Coded up to ImmolateCL line 24

// Helper functions
void Instance::lock(std::string item) {
    locked.push_back(item);
}
void Instance::unlock(std::string item) {
    auto it = std::find(locked.begin(), locked.end(), item);
    if (it != locked.end()) locked.erase(it);
}
bool Instance::isLocked(std::string item) {
    return std::find(locked.begin(), locked.end(), item) != locked.end();
}

// Standard Packs
Card Instance::nextStandardCard(int ante) {
    std::string anteStr = std::to_string(ante);

    // Enhancement
    std::string enhancement;
    if (random("stdset"+anteStr) <= 0.6) enhancement = "No Enhancement";
    else enhancement = randchoice("Enhancedsta"+anteStr, ENHANCEMENTS);

    // Base
    std::string base = randchoice("frontsta"+anteStr, CARDS);

    // Edition
    std::string edition;
    double editionPoll = random("standard_edition"+anteStr);
    if (editionPoll > 0.988) edition = "Polychrome";
    else if (editionPoll > 0.96) edition = "Holographic";
    else if (editionPoll > 0.92) edition = "Foil";
    else edition = "No Edition";

    // Seal
    std::string seal;
    if (random("stdseal"+anteStr) <= 0.8) seal = "No Seal";
    else {
        double sealPoll = random("stdsealtype"+anteStr);
        if (sealPoll > 0.75) seal = "Red Seal";
        else if (sealPoll > 0.5) seal = "Blue Seal";
        else if (sealPoll > 0.25) seal = "Gold Seal";
        else seal = "Purple Seal";
    }

    return Card(base, enhancement, edition, seal);
}

// Vouchers
bool Instance::isVoucherActive(std::string voucher) {
    return std::count(params.vouchers.begin(), params.vouchers.end(), voucher) > 0;
}
void Instance::activateVoucher(std::string voucher) {
    params.vouchers.push_back(voucher);
    lock(voucher);
    // Unlock next level voucher
    for (int i = 0; i < VOUCHERS.size(); i+=2) {
        if (VOUCHERS[i] == voucher) {
            unlock(VOUCHERS[i+1]);
        };
    };
};