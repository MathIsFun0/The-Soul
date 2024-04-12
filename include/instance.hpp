#include <map>
#include <string>

struct Cache {
    std::map<std::string, double> nodes;
    bool generatedFirstPack;
};

// Todo: Add Item enum and incorporate it. Using ints for now
struct InstParams {
    int deck;
    int stake;
    bool showman;
    std::map<int, bool> vouchers;
};

struct Instance {
    std::map<int, bool> locked;
    std::string seed;
    double hashedSeed;
    Cache cache;
    InstParams params;
    LuaRandom rng;
    Instance(std::string s) {
        seed = s;
        hashedSeed = pseudohash(s);
        //todo: initialize params
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
};

// Bindings for JS
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;
EMSCRIPTEN_BINDINGS(Immolate) {
    class_<Instance>("Instance")
        .constructor<std::string>()
        .function("get_node", &Instance::get_node)
        .function("random", &Instance::random);
}
#endif