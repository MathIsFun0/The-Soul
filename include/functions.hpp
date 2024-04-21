#include <string>
#include <algorithm>
#include "instance.hpp"
// Coded up to ImmolateCL line 380

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

// Card Generators
std::string Instance::nextTarot(std::string source, int ante, bool soulable) {
    // Todo: Account for Omen Globe
    std::string anteStr = std::to_string(ante);
    if (soulable && (params.showman || !isLocked("The Soul")) && random("soul_Tarot"+anteStr) > 0.997) {
        return "The Soul";
    }
    return randchoice("Tarot"+source+anteStr, TAROTS);
}

std::string Instance::nextPlanet(std::string source, int ante, bool soulable) {
    std::string anteStr = std::to_string(ante);
    if (soulable && (params.showman || !isLocked("Black Hole")) && random("soul_Planet"+anteStr) > 0.997) {
        return "Black Hole";
    }
    return randchoice("Planet"+source+anteStr, PLANETS);
}

std::string Instance::nextSpectral(std::string source, int ante, bool soulable) {
    std::string anteStr = std::to_string(ante);
    if (soulable) {
        std::string forcedKey = "RETRY";
        if ((params.showman || !isLocked("The Soul")) && random("soul_Spectral"+anteStr) > 0.997) forcedKey = "The Soul";
        if ((params.showman || !isLocked("Black Hole")) && random("soul_Spectral"+anteStr) > 0.997) forcedKey = "Black Hole";
        if (forcedKey != "RETRY") return forcedKey;
    }
    return randchoice("Spectral"+source+anteStr, SPECTRALS);
}

JokerData Instance::nextJoker(std::string source, int ante) {
    std::string anteStr = std::to_string(ante);

    // Get rarity
    std::string rarity;
    if (source == "sou") rarity = "4";
    else if (source == "wra") rarity = "3";
    else if (source == "rta") rarity = "3";
    else if (source == "uta") rarity = "2";
    else {
        double rarityPoll = random("rarity"+anteStr+source);
        if (rarityPoll > 0.95) rarity = "3";
        else if (rarityPoll > 0.7) rarity = "2";
        else rarity = "1";
    }

    // Get edition
    // TODO: account for Hone
    std::string edition;
    double editionPoll = random("edi"+source+anteStr);
    if (editionPoll > 0.997) edition = "Negative";
    else if (editionPoll > 0.994) edition = "Polychrome";
    else if (editionPoll > 0.98) edition = "Holographic";
    else if (editionPoll > 0.96) edition = "Foil";
    else edition = "No Edition";

    // Get next joker
    std::string joker;
    if (rarity == "4") joker = randchoice("Joker4", LEGENDARY_JOKERS);
    else if (rarity == "3") joker = randchoice("Joker3"+source+anteStr, RARE_JOKERS);
    else if (rarity == "2") joker = randchoice("Joker2"+source+anteStr, UNCOMMON_JOKERS);
    else if (rarity == "1") joker = randchoice("Joker1"+source+anteStr, COMMON_JOKERS);

    // Get next joker stickers
    JokerStickers stickers = JokerStickers();
    if (params.stake == "Black Stake" || params.stake == "Blue Stake" || params.stake == "Purple Stake" || params.stake == "Orange Stake" || params.stake == "Gold Stake") {
        if (joker != "Gros Michel" && joker != "Ice Cream" && joker != "Cavendish" && joker != "Luchador"
         && joker != "Turtle Bean" && joker != "Diet Cola" && joker != "Popcorn"   && joker != "Ramen"
         && joker != "Seltzer"     && joker != "Mr. Bones" && joker != "Invisible Joker") {
            stickers.eternal = random("stake_shop_joker_eternal"+anteStr) > 0.7;
         }
    }
    if (params.stake == "Orange Stake" || params.stake == "Gold Stake" && !stickers.eternal) {
        stickers.perishable = random("ssjp"+anteStr) > 0.49;
    }
    if (params.stake == "Gold Stake") {
        stickers.rental = random("ssjr"+anteStr) > 0.7;
    }

    return JokerData(joker, rarity, edition, stickers);
}

// Shop Logic
ShopInstance Instance::getShopInstance() {
    double tarotRate = 4;
    double planetRate = 4;
    double playingCardRate = 0;
    double spectralRate = 0;
    if (params.deck == "Ghost Deck") {
        spectralRate = 2;
    }
    if (isVoucherActive("Tarot Tycoon")) {
        tarotRate = 32;
    } else if (isVoucherActive("Tarot Merchant")) {
        tarotRate = 9.6;
    }
    if (isVoucherActive("Planet Tycoon")) {
        planetRate = 32;
    } else if (isVoucherActive("Planet Merchant")) {
        planetRate = 9.6;
    }
    if (isVoucherActive("Magic Trick")) {
        playingCardRate = 4;
    }

    return ShopInstance(20, tarotRate, planetRate, playingCardRate, spectralRate);
};

ShopItem Instance::nextShopItem(int ante) {
    std::string anteStr = std::to_string(ante);

    ShopInstance shop = getShopInstance();
    double cdtPoll = random("cdt"+anteStr) * shop.getTotalRate();
    std::string type;
    if (cdtPoll < shop.jokerRate) type = "Joker";
    else {cdtPoll -= shop.jokerRate;
    if (cdtPoll < shop.tarotRate) type = "Tarot";
    else {cdtPoll -= shop.tarotRate;
    if (cdtPoll < shop.planetRate) type = "Planet";
    else {cdtPoll -= shop.planetRate;
    if (cdtPoll < shop.playingCardRate) type = "Playing Card";
    else type = "Spectral";}}}

    if (type == "Joker") {
        JokerData jkr = nextJoker("sho", ante);
        return ShopItem(type, jkr.joker, jkr);
    } else if (type == "Tarot") {
        return ShopItem(type, nextTarot("sho", ante, false));
    } else if (type == "Planet") {
        return ShopItem(type, nextPlanet("sho", ante, false));
    } else if (type == "Spectral") {
        return ShopItem(type, nextSpectral("sho", ante, false));
    }
    // Todo: Magic Trick support
    return ShopItem();
}

// Packs and Pack Contents
std::string Instance::nextPack(int ante) {
    if (ante <= 2 && !cache.generatedFirstPack) {
        cache.generatedFirstPack = true;
        return "Buffoon Pack";
    }
    std::string anteStr = std::to_string(ante);
    return randweightedchoice("shop_pack"+anteStr, PACKS);
}
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