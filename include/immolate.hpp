#include "util.hpp"
#include "instance.hpp"
#include "items.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;
EMSCRIPTEN_BINDINGS(Immolate) {
    //instance.hpp
    register_vector<std::string>("VectorStr");
    class_<Instance>("Instance")
        .constructor<std::string>()
        .function("get_node", &Instance::get_node)
        .function("random", &Instance::random)
        .function("randint", &Instance::randint)
        .function("randchoice", &Instance::randchoice);

    //items.hpp
    constant("ENHANCEMENTS", &ENHANCEMENTS);
    constant("CARDS", &CARDS);
    constant("SUITS", &SUITS);
    constant("RANKS", &RANKS);
    constant("TAROTS", &TAROTS);
    constant("PLANETS", &PLANETS);
    constant("COMMON_JOKERS", &COMMON_JOKERS);
    constant("UNCOMMON_JOKERS", &UNCOMMON_JOKERS);
    constant("RARE_JOKERS", &RARE_JOKERS);
    constant("LEGENDARY_JOKERS", &LEGENDARY_JOKERS);
    constant("VOUCHERS", &VOUCHERS);
    constant("SPECTRALS", &SPECTRALS);
    constant("TAGS", &TAGS);
    constant("BOSSES", &BOSSES);
}
#endif