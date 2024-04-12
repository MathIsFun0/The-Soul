#include <string>
#include <vector>

const unsigned long long MAX_UINT64 = 18446744073709551615ull;

typedef union DoubleLong {
    double dbl;
    unsigned long long ulong;
} dbllong;

struct LuaRandom {
    unsigned long long state[4];
    LuaRandom(double seed) {
        double d = seed;
        unsigned long long r = 0x11090601;
        for (int i = 0; i < 4; i++) {
            unsigned long long m = 1ull << (r & 255);
            r >>= 8;
            d = d * 3.14159265358979323846 + 2.7182818284590452354;
            dbllong u;
            u.dbl = d;
            if (u.ulong < m) u.ulong += m;
            state[i] = u.ulong;
        }
        for (int i = 0; i < 10; i++) {
            _randint();
        }
    }
    LuaRandom() {
        LuaRandom(0);
    }
    unsigned long long _randint() {
        unsigned long long z = 0;
        unsigned long long r = 0;
        z = state[0];
        z = (((z<<31ull)^z)>>45ull)^((z&(MAX_UINT64<<1ull))<<18ull);
        r ^= z;
        state[0] = z;
        z = state[1];
        z = (((z<<19ull)^z)>>30ull)^((z&(MAX_UINT64<<6ull))<<28ull);
        r ^= z;
        state[1] = z;
        z = state[2];
        z = (((z<<24ull)^z)>>48ull)^((z&(MAX_UINT64<<9ull))<<7ull);
        r ^= z;
        state[2] = z;
        z = state[3];
        z = (((z<<21ull)^z)>>39ull)^((z&(MAX_UINT64<<17ull))<<8ull);
        r ^= z;
        state[3] = z;
        return r;
    }
    unsigned long long randdblmem() {        
        return (_randint() & 4503599627370495ull) | 4607182418800017408ull;
    }
    double random() {
        dbllong u;
        u.ulong = randdblmem();
        return u.dbl - 1.0;
    }
    int randint(int min, int max) {
        return (int)(random()*(max-min+1))+min;
    }
};

double fract(double n) {
    return n - (long)n;
};

double pseudohash(std::string s) {
    double num = 1;
    for (size_t i = s.length(); i > 0; i--) {
        num = fract(1.1239285023/num*s[i-1]*3.141592653589793116+3.141592653589793116*i);
    }
    return num;
};