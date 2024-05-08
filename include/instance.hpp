#include <map>
#include <iomanip>
#include <string>
#pragma once

struct Cache {
    std::map<std::string, double> nodes;
    bool generatedFirstPack;
};

struct InstParams {
    std::string deck;
    std::string stake;
    bool showman;
    int sixesFactor;
    long version;
    std::vector<std::string> vouchers;
    InstParams() {
        deck = "Red Deck";
        stake = "White Stake";
        showman = false;
        sixesFactor = 1;
        version = 10103; //1.0.1c
    }
    InstParams(std::string d, std::string s, bool show, long v) {
        deck = d;
        stake = s;
        showman = show;
        sixesFactor = 1;
        version = v;
    }
};

struct Instance {
    std::vector<std::string> locked;
    std::string seed;
    double hashedSeed;
    Cache cache;
    InstParams params;
    LuaRandom rng;
    Instance(std::string s) {
        seed = s;
        hashedSeed = pseudohash(s);
        params = InstParams();
        rng = LuaRandom(0);
        cache.generatedFirstPack = false;
    };
    double get_node(std::string ID) {
        if (cache.nodes.count(ID) == 0) {
            cache.nodes[ID] = pseudohash(ID+seed);
        }
        cache.nodes[ID] = round13(std::fmod(cache.nodes[ID]*1.72431234+2.134453429141,1));
        return (cache.nodes[ID] + hashedSeed)/2;
    }
    double random(std::string ID) {
        rng = LuaRandom(get_node(ID));
        return rng.random();
    }
    int randint(std::string ID, int min, int max) {
        rng = LuaRandom(get_node(ID));
        return rng.randint(min, max);
    }
    std::string randchoice(std::string ID, std::vector<std::string> items) {
        rng = LuaRandom(get_node(ID));
        std::string item = items[rng.randint(0, items.size()-1)];
        if ((params.showman == false && isLocked(item)) || item == "RETRY") {
            int resample = 2;
            while (true) {
                rng = LuaRandom(get_node(ID+"_resample"+std::to_string(resample)));
                std::string item = items[rng.randint(0, items.size()-1)];
                resample++;
                if ((item != "RETRY" && !isLocked(item)) || resample > 1000) return item;
            }
        }
        return item;
    }
    std::string randweightedchoice(std::string ID, std::vector<WeightedItem> items) {
        rng = LuaRandom(get_node(ID));
        double poll = rng.random()*items[0].weight;
        int idx = 1;
        double weight = 0;
        while (weight < poll) {
            weight += items[idx].weight;
            idx++;
        }
        return items[idx-1].item;
    }

    // Functions defined in functions.hpp
    void lock(std::string item);
    void unlock(std::string item);
    bool isLocked(std::string item);
    void initLocks(int ante, bool freshProfile, bool freshRun);
    void initUnlocks(int ante, bool freshProfile);
    std::string nextTarot(std::string source, int ante, bool soulable);
    std::string nextPlanet(std::string source, int ante, bool soulable);
    std::string nextSpectral(std::string source, int ante, bool soulable);
    JokerData nextJoker(std::string source, int ante, bool hasStickers);
    ShopInstance getShopInstance();
    ShopItem nextShopItem(int ante);
    std::string nextPack(int ante);
    std::vector<std::string> nextArcanaPack(int size, int ante);
    std::vector<std::string> nextCelestialPack(int size, int ante);
    std::vector<std::string> nextSpectralPack(int size, int ante);
    std::vector<JokerData> nextBuffoonPack(int size, int ante);
    std::vector<Card> nextStandardPack(int size, int ante);
    Card nextStandardCard(int ante);
    bool isVoucherActive(std::string voucher);
    void activateVoucher(std::string voucher);
    std::string nextVoucher(int ante);
    void setDeck(std::string deck);
    void setStake(std::string stake);
    std::string nextTag(int ante);
    std::string nextBoss(int ante);
};