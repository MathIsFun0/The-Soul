#include <map>
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
    std::vector<std::string> vouchers;
    InstParams() {
        deck = "Red Deck";
        stake = "White Stake";
        showman = false;
    }
    InstParams(std::string d, std::string s, bool show) {
        deck = d;
        stake = s;
        showman = show;
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
    };
    double get_node(std::string ID) {
        if (cache.nodes.count(ID) == 0) {
            cache.nodes[ID] = pseudohash(ID+seed);
        }
        cache.nodes[ID] = round(fract(cache.nodes[ID]*1.72431234+2.134453429141)*1e13)/1e13;
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
        return items[rng.randint(0, items.size()-1)];
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
    Card nextStandardCard(int ante);
    bool isVoucherActive(std::string voucher);
    void activateVoucher(std::string voucher);
};