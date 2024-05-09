#include <string>
#include <algorithm>
#include "instance.hpp"

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

// Lock initializers
void Instance::initLocks(int ante, bool freshProfile, bool freshRun) {
    if (ante < 2) {
        lock("The Mouth");
        lock("The Fish");
        lock("The Wall");
        lock("The House");
        lock("The Mark");
        lock("The Wheel");
        lock("The Arm");
        lock("The Water");
        lock("The Needle");
        lock("The Flint");
        lock("Negative Tag");
        lock("Standard Tag");
        lock("Meteor Tag");
        lock("Buffoon Tag");
        lock("Handy Tag");
        lock("Garbage Tag");
        lock("Ethereal Tag");
        lock("Top-up Tag");
        lock("Orbital Tag");
    }
    if (ante < 3) {
        lock("The Tooth");
        lock("The Eye");
    }
    if (ante < 4) lock("The Plant");
    if (ante < 5) lock("The Serpent");
    if (ante < 6) lock("The Ox");
    if (freshProfile) {
        lock("Negative Tag");
        lock("Foil Tag");
        lock("Holographic Tag");
        lock("Polychrome Tag");
        lock("Rare Tag");
        lock("Golden Ticket");
        lock("Mr. Bones");
        lock("Acrobat");
        lock("Sock and Buskin");
        lock("Swashbuckler");
        lock("Troubadour");
        lock("Certificate");
        lock("Smeared Joker");
        lock("Throwback");
        lock("Hanging Chad");
        lock("Rough Gem");
        lock("Bloodstone");
        lock("Arrowhead");
        lock("Onyx Agate");
        lock("Glass Joker");
        lock("Showman");
        lock("Flower Pot");
        lock("Blueprint");
        lock("Wee Joker");
        lock("Merry Andy");
        lock("Oops! All 6s");
        lock("The Idol");
        lock("Seeing Double");
        lock("Matador");
        lock("Hit the Road");
        lock("The Duo");
        lock("The Trio");
        lock("The Family");
        lock("The Order");
        lock("The Tribe");
        lock("Stuntman");
        lock("Invisible Joker");
        lock("Brainstorm");
        lock("Satellite");
        lock("Shoot the Moon");
        lock("Driver's License");
        lock("Cartomancer");
        lock("Astronomer");
        lock("Burnt Joker");
        lock("Bootstraps");
        lock("Overstock Plus");
        lock("Liquidation");
        lock("Glow Up");
        lock("Reroll Glut");
        lock("Omen Globe");
        lock("Observatory");
        lock("Nacho Tong");
        lock("Recyclomancy");
        lock("Tarot Tycoon");
        lock("Planet Tycoon");
        lock("Money Tree");
        lock("Antimatter");
        lock("Illusion");
        lock("Petroglyph");
        lock("Retcon");
        lock("Palette");
    }
    if (freshRun) {
        lock("Planet X");
        lock("Ceres");
        lock("Eris");
        lock("Five of a Kind");
        lock("Flush House");
        lock("Flush Five");
        lock("Stone Joker");
        lock("Steel Joker");
        lock("Glass Joker");
        lock("Golden Ticket");
        lock("Lucky Cat");
        lock("Cavendish");
        lock("Overstock Plus");
        lock("Liquidation");
        lock("Glow Up");
        lock("Reroll Glut");
        lock("Omen Globe");
        lock("Observatory");
        lock("Nacho Tong");
        lock("Recyclomancy");
        lock("Tarot Tycoon");
        lock("Planet Tycoon");
        lock("Money Tree");
        lock("Antimatter");
        lock("Illusion");
        lock("Petroglyph");
        lock("Retcon");
        lock("Palette");
    }
}
void Instance::initUnlocks(int ante, bool freshProfile) {
    if (ante == 2) {
        unlock("The Mouth");
        unlock("The Fish");
        unlock("The Wall");
        unlock("The House");
        unlock("The Mark");
        unlock("The Wheel");
        unlock("The Arm");
        unlock("The Water");
        unlock("The Needle");
        unlock("The Flint");
        if (!freshProfile) unlock("Negative Tag");
        unlock("Standard Tag");
        unlock("Meteor Tag");
        unlock("Buffoon Tag");
        unlock("Handy Tag");
        unlock("Garbage Tag");
        unlock("Ethereal Tag");
        unlock("Top-up Tag");
        unlock("Orbital Tag");
    }
    if (ante == 3) {
        unlock("The Tooth");
        unlock("The Eye");
    }
    if (ante == 4) unlock("The Plant");
    if (ante == 5) unlock("The Serpent");
    if (ante == 6) unlock("The Ox");
}

// Card Generators
std::string Instance::nextTarot(std::string source, int ante, bool soulable) {
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

JokerData Instance::nextJoker(std::string source, int ante, bool hasStickers) {
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
    int editionRate = 1;
    if (isVoucherActive("Glow Up")) editionRate = 4;
    else if (isVoucherActive("Hone")) editionRate = 2;
    std::string edition;
    double editionPoll = random("edi"+source+anteStr);
    if (editionPoll > 0.997) edition = "Negative";
    else if (editionPoll > 1 - 0.006 * editionRate) edition = "Polychrome";
    else if (editionPoll > 1 - 0.02 * editionRate) edition = "Holographic";
    else if (editionPoll > 1 - 0.04 * editionRate) edition = "Foil";
    else edition = "No Edition";

    // Get next joker
    std::string joker;
    if (rarity == "4") {
        if (params.version > 10099) joker = randchoice("Joker4", LEGENDARY_JOKERS);
        else joker = randchoice("Joker4"+source+anteStr, LEGENDARY_JOKERS);
    }
    else if (rarity == "3") joker = randchoice("Joker3"+source+anteStr, (params.version > 10103) ? RARE_JOKERS : ((params.version > 10099) ? RARE_JOKERS_101C : RARE_JOKERS_100));
    else if (rarity == "2") joker = randchoice("Joker2"+source+anteStr, (params.version > 10103) ? UNCOMMON_JOKERS : ((params.version > 10099) ? UNCOMMON_JOKERS_101C : UNCOMMON_JOKERS_100));
    else if (rarity == "1") joker = randchoice("Joker1"+source+anteStr, (params.version > 10099) ? COMMON_JOKERS : COMMON_JOKERS_100);

    // Get next joker stickers
    JokerStickers stickers = JokerStickers();
    if (hasStickers) {
        if (params.version > 10103) {
            double stickerPoll = random(((source=="buf") ? "packetper" : "etperpoll")+anteStr);
            if (stickerPoll > 0.7 && (params.stake == "Black Stake" || params.stake == "Blue Stake" || params.stake == "Purple Stake" || params.stake == "Orange Stake" || params.stake == "Gold Stake")) {
                if (joker != "Gros Michel" && joker != "Ice Cream" && joker != "Cavendish" && joker != "Luchador"
                 && joker != "Turtle Bean" && joker != "Diet Cola" && joker != "Popcorn"   && joker != "Ramen"
                 && joker != "Seltzer"     && joker != "Mr. Bones" && joker != "Invisible Joker") {
                    stickers.eternal = true;
                }
            }
            if ((stickerPoll > 0.4 && stickerPoll <= 0.7) && (params.stake == "Orange Stake" || params.stake == "Gold Stake")) {
                if (joker != "Ceremonial Dagger" && joker != "Ride the Bus"   && joker != "Runner"  && joker != "Constellation"
                 && joker != "Green Joker"       && joker != "Red Card"       && joker != "Madness" && joker != "Square Joker"
                 && joker != "Vampire"           && joker != "Rocket"         && joker != "Obelisk" && joker != "Lucky Cat"
                 && joker != "Flash Card"        && joker != "Spare Trousers" && joker != "Castle"  && joker != "Wee Joker") {
                    stickers.perishable = true;
                }
            }
            if (params.stake == "Gold Stake") {
                stickers.rental = random(((source=="buf") ? "packssjr" : "ssjr")+anteStr) > 0.7;
            }
        } else {
            if (params.stake == "Black Stake" || params.stake == "Blue Stake" || params.stake == "Purple Stake" || params.stake == "Orange Stake" || params.stake == "Gold Stake") {
                if (joker != "Gros Michel" && joker != "Ice Cream" && joker != "Cavendish" && joker != "Luchador"
                 && joker != "Turtle Bean" && joker != "Diet Cola" && joker != "Popcorn"   && joker != "Ramen"
                 && joker != "Seltzer"     && joker != "Mr. Bones" && joker != "Invisible Joker") {
                    stickers.eternal = random("stake_shop_joker_eternal"+anteStr) > 0.7;
                }
            }
            if (params.version > 10099) {
                if ((params.stake == "Orange Stake" || params.stake == "Gold Stake") && !stickers.eternal) {
                    stickers.perishable = random("ssjp"+anteStr) > 0.49;
                }
                if (params.stake == "Gold Stake") {
                    stickers.rental = random("ssjr"+anteStr) > 0.7;
                }
            }
        }
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
        JokerData jkr = nextJoker("sho", ante, true);
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
    if (ante <= 2 && !cache.generatedFirstPack && params.version > 10099) {
        cache.generatedFirstPack = true;
        return "Buffoon Pack";
    }
    std::string anteStr = std::to_string(ante);
    return randweightedchoice("shop_pack"+anteStr, PACKS);
}
Pack packInfo(std::string pack) {
    if (pack[0] == 'M') {
        return Pack(pack.substr(5), (pack[5] == 'B' || pack[6] == 'p') ? 4 : 5, 2);
    } else if (pack[0] == 'J') {
        return Pack(pack.substr(6), (pack[6] == 'B' || pack[7] == 'p') ? 4 : 5, 1);
    } else {
        return Pack(pack, (pack[0] == 'B' || pack[1] == 'p') ? 2 : 3, 1);
    }
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
std::vector<std::string> Instance::nextArcanaPack(int size, int ante) {
    std::vector<std::string> pack;
    for (int i = 0; i < size; i++) {
        if (isVoucherActive("Omen Globe") && random("omen_globe") > 0.8) {
            pack.push_back(nextSpectral("ar2", ante, true));
        } else pack.push_back(nextTarot("ar1", ante, true));
        if (!params.showman) lock(pack[i]);
    }
    for (int i = 0; i < size; i++) unlock(pack[i]);
    return pack;
}
std::vector<std::string> Instance::nextCelestialPack(int size, int ante) {
    std::vector<std::string> pack;
    for (int i = 0; i < size; i++) {
        pack.push_back(nextPlanet("pl1", ante, true));
        if (!params.showman) lock(pack[i]);
    }
    for (int i = 0; i < size; i++) unlock(pack[i]);
    return pack;
}
std::vector<std::string> Instance::nextSpectralPack(int size, int ante) {
    std::vector<std::string> pack;
    for (int i = 0; i < size; i++) {
        pack.push_back(nextSpectral("spe", ante, true));
        if (!params.showman) lock(pack[i]);
    }
    for (int i = 0; i < size; i++) unlock(pack[i]);
    return pack;
}
std::vector<Card> Instance::nextStandardPack(int size, int ante) {
    std::vector<Card> pack;
    for (int i = 0; i < size; i++) {
        pack.push_back(nextStandardCard(ante));
    }
    return pack;
}
std::vector<JokerData> Instance::nextBuffoonPack(int size, int ante) {
    std::vector<JokerData> pack;
    for (int i = 0; i < size; i++) {
        pack.push_back(nextJoker("buf", ante, true));
        if (!params.showman) lock(pack[i].joker);
    }
    for (int i = 0; i < size; i++) unlock(pack[i].joker);
    return pack;
}
// Misc
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

std::string Instance::nextVoucher(int ante) {
    return randchoice("Voucher"+std::to_string(ante), VOUCHERS);
}

void Instance::setDeck(std::string deck) {
    params.deck = deck;
    if (deck == "Magic Deck") {
        activateVoucher("Crystal Ball");
    }
    if (deck == "Nebula Deck") {
        activateVoucher("Telescope");
    }
    if (deck == "Zodiac Deck") {
        activateVoucher("Tarot Merchant");
        activateVoucher("Planet Merchant");
        activateVoucher("Overstock");
    }
}

void Instance::setStake(std::string stake) {
    params.stake = stake;
}

std::string Instance::nextTag(int ante) {
    return randchoice("Tag"+std::to_string(ante), TAGS);
}

std::string Instance::nextBoss(int ante) {
    std::vector<std::string> bossPool;
    int numBosses = 0;
    for (int i = 0; i < BOSSES.size(); i++) {
        if (!isLocked(BOSSES[i])) {
            if ((ante % 8 == 0 && BOSSES[i][0] != 'T') || (ante % 8 != 0 && BOSSES[i][0] == 'T')) {
                bossPool.push_back(BOSSES[i]);
                numBosses++;
            }
        }
    }
    if (numBosses == 0) {
        for (int i = 0; i < BOSSES.size(); i++) {
            if ((ante % 8 == 0 && BOSSES[i][0] != 'T') || (ante % 8 != 0 && BOSSES[i][0] == 'T')) {
                unlock(BOSSES[i]);
            }
        }
        return nextBoss(ante);
    }
    std::string chosenBoss = randchoice("boss", bossPool);
    lock(chosenBoss);
    return chosenBoss;
}