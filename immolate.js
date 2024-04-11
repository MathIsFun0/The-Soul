// Utility functions for type punning in JS

// Convert a 64-bit float to a 64-bit integer
function float64ToInt64(value) {
    const view = new DataView(new ArrayBuffer(8));
    view.setFloat64(0, value);
    return view.getBigInt64(0);
}

// Convert a 64-bit integer to a 64-bit float
function int64ToFloat64(value) {
    const view = new DataView(new ArrayBuffer(8));
    view.setBigInt64(0, BigInt(value));
    return view.getFloat64(0);
}

// Some more util for this
const MAX_UINT64 = 2n ** 64n - 1n;
function lshift64(x, y) {
    return (x << y) & MAX_UINT64;
}

// Port of LuaJIT's math.random()
// The state is a list of 4 64-bit unsigned integers
class LuaRandom {
    constructor(seed) {
        var d = seed;
        var r = 0x11090601n;
        this.state = [0n, 0n, 0n, 0n]
        for (let i = 0; i < 4; i++) {
            var m = 1n << (r & 255n);
            r >>= 8n;
            d = d * 3.14159265358979323846 + 2.7182818284590452354;
            var u = float64ToInt64(d);
            if (u < m) u += m;
            this.state[i] = u;
        }
        console.log(this.state);
        for (let i = 0; i < 10; i++) {
            this._randint()
        }
    }
    _randint() {
        var z, r = 0n;
        z = this.state[0];
        z = ((lshift64(z,31n)^z)>>45n)^lshift64(z&lshift64(MAX_UINT64,1n),18n);
        r ^= z & MAX_UINT64;
        this.state[0] = z;
        z = this.state[1];
        z = ((lshift64(z,19n)^z)>>30n)^lshift64(z&lshift64(MAX_UINT64,6n),28n);
        r ^= z & MAX_UINT64;
        this.state[1] = z;
        z = this.state[2];
        z = ((lshift64(z,24n)^z)>>48n)^lshift64(z&lshift64(MAX_UINT64,9n),7n);
        r ^= z & MAX_UINT64;
        this.state[2] = z;
        z = this.state[3];
        z = ((lshift64(z,21n)^z)>>39n)^lshift64(z&lshift64(MAX_UINT64,17n),8n);
        r ^= z & MAX_UINT64;
        this.state[3] = z;
        return r;
    }
    randdblmem() {
        return (this._randint() & 4503599627370495n) | 4607182418800017408n;
    }
    random() {
        return int64ToFloat64(this.randdblmem()) - 1.0;
    }
    randint(min, max) {
        return Math.floor(random()*(max-min+1))+min;
    }
}

// Pseudohash algorithm
function fract(n) {
    return n - Math.floor(n);
}
function pseudohash(s) {
    var num = 1;
    for (var i = s.length - 1; i >= 0; i--) {
        num = fract(1.1239285023/num*s.charCodeAt(i)*3.141592653589793116+3.141592653589793116*(i+1));
    }
    console.log(num)
    return num;
}

// RNG Cache
const RNGType = {
    Joker_Common: "Joker1",
    Joker_Uncommon: "Joker2",
    Joker_Rare: "Joker3",
    Joker_Legendary: "Joker4",
    Joker_Rarity: "rarity",
    Joker_Edition: "edi",
    Misprint: "misprint",
    Standard_Has_Enhancement: "stdset",
    Enhancement: "Enhanced",
    Card: "front",
    Standard_Edition: "standard_edition",
    Standard_Has_Seal: "stdseal",
    Standard_Seal: "stdsealtype",
    Shop_Pack: "shop_pack",
    Tarot: "Tarot",
    Spectral: "Spectral",
    Tags: "Tag",
    Shuffle_New_Round: "nr",
    Card_Type: "cdt",
    Planet: "Planet",
    Lucky_Mult: "lucky_mult",
    Lucky_Money: "lucky_money",
    Sigil: "sigil",
    Ouija: "ouija",
    Wheel_of_Fortune: "wheel_of_fortune",
    Gros_Michel: "gros_michel",
    Cavendish: "cavendish",
    Voucher: "Voucher",
    Voucher_Tag: "Voucher_fromtag",
    Soul: "soul_",
    Erratic: "erratic",
    Eternal: "stake_shop_joker_eternal",
    Perishable: "ssjp",
    Rental: "ssjr",
    Boss: "boss"
}

const RNGSource = {
    Shop: "sho",
    Emperor: "emp",
    High_Priestess: "pri",
    Judgement: "jud",
    Wraith: "wra",
    Arcana: "ar1",
    Celestial: "pl1",
    Spectral: "spe",
    Standard: "sta",
    Buffoon: "buf",
    Vagabond: "vag",
    Superposition: "sup",
    _8_Ball: "8ba",
    Seance: "sea",
    Sixth_Sense: "sixth",
    Top_Up: "top",
    Rare_Tag: "rta",
    Uncommon_Tag: "uta",
    Blue_Seal: "blusl",
    Purple_Seal: "8ba",
    Soul: "sou"
}

class Cache {
    constructor() {
        this.nodes = {};
        this.generatedFirstPack = false;
    }
}

class Instance {
    constructor(seed) {
        this.locked = {};
        this.seed = seed;
        this.hashedSeed = pseudohash(seed);
        this.cache = new Cache();
        this.params = {
            deck: "Red",
            stake: "White",
            showman: false,
            vouchers: {}
        }
        this.rng = new LuaRandom(0);
    }
    get_node(ID) {
        if (!(ID in this.cache)) {
            this.cache[ID] = pseudohash(ID+this.seed);
        }
        this.cache[ID] = parseFloat(fract(this.cache[ID]*1.72431234+2.134453429141).toFixed(13));
        console.log((this.cache[ID] + this.hashedSeed)/2)
        return (this.cache[ID] + this.hashedSeed)/2;
    }
    random(ID) {
        this.rng = new LuaRandom(this.get_node(ID));
        return this.rng.random();
    }
}

// Miniature example
var inst = new Instance("IMMOLATE");
console.log(inst.random(RNGType.Erratic));