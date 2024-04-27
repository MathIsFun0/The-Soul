#include <string>
#include <vector>

// Structs for storing information
struct ShopInstance {
    double jokerRate;
    double tarotRate;
    double planetRate;
    double playingCardRate;
    double spectralRate;
    ShopInstance() {
        jokerRate = 20;
        tarotRate = 4;
        planetRate = 4;
        playingCardRate = 0;
        spectralRate = 0;
    };
    ShopInstance(double j, double t, double p, double c, double s) {
        jokerRate = j;
        tarotRate = t;
        planetRate = p;
        playingCardRate = c;
        spectralRate = s;
    }
    double getTotalRate() {
        return jokerRate + tarotRate + planetRate + playingCardRate + spectralRate;
    }
};

struct JokerStickers {
    bool eternal;
    bool perishable;
    bool rental;
    JokerStickers() {
        eternal = false;
        perishable = false;
        rental = false;
    };
    JokerStickers(bool e, bool p, bool r) {
        eternal = e;
        perishable = p;
        rental = r;
    }
};

struct JokerData {
    std::string joker;
    std::string rarity;
    std::string edition;
    JokerStickers stickers;
    JokerData() {
        joker = "Joker";
        rarity = "Common";
        edition = "No Edition";
        stickers = JokerStickers();
    };
    JokerData(std::string j, std::string r, std::string e, JokerStickers s) {
        joker = j;
        rarity = r;
        edition = e;
        stickers = s;
    };
};

struct ShopItem {
    std::string type;
    std::string item;
    JokerData jokerData;
    ShopItem() {
        type = "Tarot";
        item = "The Fool";
    };
    ShopItem(std::string t, std::string i) {
        type = t;
        item = i;
    };
    ShopItem(std::string t, std::string i, JokerData j) {
        type = t;
        item = i;
        jokerData = j;
    };
};

struct WeightedItem {
    std::string item;
    double weight;
    WeightedItem(std::string i, double w) {
        item = i;
        weight = w;
    };
};

struct Pack {
    std::string type;
    int size;
    int choices;
    Pack(std::string t, int s, int c) {
        type = t;
        size = s;
        choices = c;
    }
};

struct Card {
    std::string base;
    std::string enhancement;
    std::string edition;
    std::string seal;
    Card(std::string b, std::string n, std::string e, std::string s) {
        base = b;
        enhancement = n;
        edition = e;
        seal = s;
    }
};

std::vector<std::string> ENHANCEMENTS = {
    "Bonus",
    "Mult",
    "Wild",
    "Glass",
    "Steel",
    "Stone",
    "Gold",
    "Lucky"
};

std::vector<std::string> CARDS = {
    "C_2",
    "C_3",
    "C_4",
    "C_5",
    "C_6",
    "C_7",
    "C_8",
    "C_9",
    "C_A",
    "C_J",
    "C_K",
    "C_Q",
    "C_T",
    "D_2",
    "D_3",
    "D_4",
    "D_5",
    "D_6",
    "D_7",
    "D_8",
    "D_9",
    "D_A",
    "D_J",
    "D_K",
    "D_Q",
    "D_T",
    "H_2",
    "H_3",
    "H_4",
    "H_5",
    "H_6",
    "H_7",
    "H_8",
    "H_9",
    "H_A",
    "H_J",
    "H_K",
    "H_Q",
    "H_T",
    "S_2",
    "S_3",
    "S_4",
    "S_5",
    "S_6",
    "S_7",
    "S_8",
    "S_9",
    "S_A",
    "S_J",
    "S_K",
    "S_Q",
    "S_T"
};

std::vector<std::string> SUITS = {
    "Spades",
    "Hearts",
    "Clubs",
    "Diamonds"
};

std::vector<std::string> RANKS = {
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "Jack",
    "Queen",
    "King",
    "Ace"
};

std::vector<WeightedItem> PACKS = {
    WeightedItem("RETRY", 22.42),
    WeightedItem("Arcana Pack", 4),
    WeightedItem("Jumbo Arcana Pack", 2),
    WeightedItem("Mega Arcana Pack", 0.5),
    WeightedItem("Celestial Pack", 4),
    WeightedItem("Jumbo Celestial Pack", 2),
    WeightedItem("Mega Celestial Pack", 0.5),
    WeightedItem("Standard Pack", 4),
    WeightedItem("Jumbo Standard Pack", 2),
    WeightedItem("Mega Standard Pack", 0.5),
    WeightedItem("Buffoon Pack", 1.2),
    WeightedItem("Jumbo Buffoon Pack", 0.6),
    WeightedItem("Mega Buffoon Pack", 0.15),
    WeightedItem("Spectral Pack", 0.6),
    WeightedItem("Jumbo Spectral Pack", 0.3),
    WeightedItem("Mega Spectral Pack", 0.07)
};

std::vector<std::string> TAROTS = {
    "The Fool",
    "The Magician",
    "The High Priestess",
    "The Empress",
    "The Emperor",
    "The Hierophant",
    "The Lovers",
    "The Chariot",
    "Justice",
    "The Hermit",
    "The Wheel of Fortune",
    "Strength",
    "The Hanged Man",
    "Death",
    "Temperance",
    "The Devil",
    "The Tower",
    "The Star",
    "The Moon",
    "The Sun",
    "Judgement",
    "The World"
};

std::vector<std::string> PLANETS = {
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "Jupiter",
    "Saturn",
    "Uranus",
    "Neptune",
    "Pluto",
    "Planet X",
    "Ceres",
    "Eris"
};

std::vector<std::string> COMMON_JOKERS_100 = {
    "Joker",
    "Greedy Joker",
    "Lusty Joker",
    "Wrathful Joker",
    "Gluttonous Joker",
    "Jolly Joker",
    "Zany Joker",
    "Mad Joker",
    "Crazy Joker",
    "Droll Joker",
    "Sly Joker",
    "Wily Joker",
    "Clever Joker",
    "Devious Joker",
    "Crafty Joker",
    "Half Joker",
    "Credit Card",
    "Banner",
    "Mystic Summit",
    "8 Ball",
    "Misprint",
    "Raised Fist",
    "Chaos the Clown",
    "Scary Face",
    "Abstract Joker",
    "Delayed Gratification",
    "Gros Michel",
    "Even Steven",
    "Odd Todd",
    "Scholar",
    "Business Card",
    "Supernova",
    "Ride the Bus",
    "Egg",
    "Runner",
    "Ice Cream",
    "Splash",
    "Blue Joker",
    "Faceless Joker",
    "Green Joker",
    "Superposition",
    "To Do List",
    "Cavendish",
    "Red Card",
    "Square Joker",
    "Riff-raff",
    "Photograph",
    "Mail In Rebate",
    "Hallucination",
    "Fortune Teller",
    "Juggler",
    "Drunkard",
    "Golden Joker",
    "Popcorn",
    "Walkie Talkie",
    "Smiley Face",
    "Golden Ticket",
    "Swashbuckler",
    "Hanging Chad",
    "Shoot the Moon"
};

std::vector<std::string> COMMON_JOKERS = {
    "Joker",
    "Greedy Joker",
    "Lusty Joker",
    "Wrathful Joker",
    "Gluttonous Joker",
    "Jolly Joker",
    "Zany Joker",
    "Mad Joker",
    "Crazy Joker",
    "Droll Joker",
    "Sly Joker",
    "Wily Joker",
    "Clever Joker",
    "Devious Joker",
    "Crafty Joker",
    "Half Joker",
    "Credit Card",
    "Banner",
    "Mystic Summit",
    "8 Ball",
    "Misprint",
    "Raised Fist",
    "Chaos the Clown",
    "Scary Face",
    "Abstract Joker",
    "Delayed Gratification",
    "Gros Michel",
    "Even Steven",
    "Odd Todd",
    "Scholar",
    "Business Card",
    "Supernova",
    "Ride the Bus",
    "Egg",
    "Runner",
    "Ice Cream",
    "Splash",
    "Blue Joker",
    "Faceless Joker",
    "Green Joker",
    "Superposition",
    "To Do List",
    "Cavendish",
    "Red Card",
    "Square Joker",
    "Riff-raff",
    "Photograph",
    "Reserved Parking",
    "Mail In Rebate",
    "Hallucination",
    "Fortune Teller",
    "Juggler",
    "Drunkard",
    "Golden Joker",
    "Popcorn",
    "Walkie Talkie",
    "Smiley Face",
    "Golden Ticket",
    "Swashbuckler",
    "Hanging Chad",
    "Shoot the Moon"
};

std::vector<std::string> UNCOMMON_JOKERS_100 = {
    "Joker Stencil",
    "Four Fingers",
    "Mime",
    "Ceremonial Dagger",
    "Marble Joker",
    "Loyalty Card",
    "Dusk",
    "Fibonacci",
    "Steel Joker",
    "Hack",
    "Pareidolia",
    "Space Joker",
    "Burglar",
    "Blackboard",
    "Constellation",
    "Hiker",
    "Card Sharp",
    "Madness",
    "Vampire",
    "Shortcut",
    "Hologram",
    "Vagabond",
    "Cloud 9",
    "Rocket",
    "Midas Mask",
    "Luchador",
    "Gift Card",
    "Turtle Bean",
    "Erosion",
    "Reserved Parking",
    "To the Moon",
    "Stone Joker",
    "Lucky Cat",
    "Bull",
    "Diet Cola",
    "Trading Card",
    "Flash Card",
    "Spare Trousers",
    "Ramen",
    "Seltzer",
    "Castle",
    "Mr. Bones",
    "Acrobat",
    "Sock and Buskin",
    "Troubadour",
    "Certificate",
    "Smeared Joker",
    "Throwback",
    "Rough Gem",
    "Bloodstone",
    "Arrowhead",
    "Onyx Agate",
    "Glass Joker",
    "Showman",
    "Flower Pot",
    "Merry Andy",
    "Oops! All 6s",
    "The Idol",
    "Seeing Double",
    "Matador",
    "Stuntman",
    "Satellite",
    "Cartomancer",
    "Astronomer",
    "Burnt Joker",
    "Bootstraps"
};

std::vector<std::string> UNCOMMON_JOKERS_101C = {
    "Joker Stencil",
    "Four Fingers",
    "Mime",
    "Ceremonial Dagger",
    "Marble Joker",
    "Loyalty Card",
    "Dusk",
    "Fibonacci",
    "Steel Joker",
    "Hack",
    "Pareidolia",
    "Space Joker",
    "Burglar",
    "Blackboard",
    "Sixth Sense",
    "Constellation",
    "Hiker",
    "Card Sharp",
    "Madness",
    "Seance",
    "Shortcut",
    "Hologram",
    "Cloud 9",
    "Rocket",
    "Midas Mask",
    "Luchador",
    "Gift Card",
    "Turtle Bean",
    "Erosion",
    "To the Moon",
    "Stone Joker",
    "Lucky Cat",
    "Bull",
    "Diet Cola",
    "Trading Card",
    "Flash Card",
    "Spare Trousers",
    "Ramen",
    "Seltzer",
    "Castle",
    "Mr. Bones",
    "Acrobat",
    "Sock and Buskin",
    "Troubadour",
    "Certificate",
    "Smeared Joker",
    "Throwback",
    "Rough Gem",
    "Bloodstone",
    "Arrowhead",
    "Onyx Agate",
    "Glass Joker",
    "Showman",
    "Flower Pot",
    "Merry Andy",
    "Oops! All 6s",
    "The Idol",
    "Seeing Double",
    "Matador",
    "Stuntman",
    "Satellite",
    "Cartomancer",
    "Astronomer",
    "Bootstraps"
};

std::vector<std::string> UNCOMMON_JOKERS = {
    "Joker Stencil",
    "Four Fingers",
    "Mime",
    "Ceremonial Dagger",
    "Marble Joker",
    "Loyalty Card",
    "Dusk",
    "Fibonacci",
    "Steel Joker",
    "Hack",
    "Pareidolia",
    "Space Joker",
    "Burglar",
    "Blackboard",
    "Sixth Sense",
    "Constellation",
    "Hiker",
    "Card Sharp",
    "Madness",
    "Seance",
    "Vampire",
    "Shortcut",
    "Hologram",
    "Cloud 9",
    "Rocket",
    "Midas Mask",
    "Luchador",
    "Gift Card",
    "Turtle Bean",
    "Erosion",
    "To the Moon",
    "Stone Joker",
    "Lucky Cat",
    "Bull",
    "Diet Cola",
    "Trading Card",
    "Flash Card",
    "Spare Trousers",
    "Ramen",
    "Seltzer",
    "Castle",
    "Mr. Bones",
    "Acrobat",
    "Sock and Buskin",
    "Troubadour",
    "Certificate",
    "Smeared Joker",
    "Throwback",
    "Rough Gem",
    "Bloodstone",
    "Arrowhead",
    "Onyx Agate",
    "Glass Joker",
    "Showman",
    "Flower Pot",
    "Merry Andy",
    "Oops! All 6s",
    "The Idol",
    "Seeing Double",
    "Matador",
    "Satellite",
    "Cartomancer",
    "Astronomer",
    "Bootstraps"
};

std::vector<std::string> RARE_JOKERS_100 = {
    "DNA",
    "Sixth Sense",
    "Seance",
    "Baron",
    "Obelisk",
    "Baseball Card",
    "Ancient Joker",
    "Campfire",
    "Blueprint",
    "Wee Joker",
    "Hit the Road",
    "The Duo",
    "The Trio",
    "The Family",
    "The Order",
    "The Tribe",
    "Invisible Joker",
    "Brainstorm",
    "Drivers License"
};

std::vector<std::string> RARE_JOKERS_101C = {
    "DNA",
    "Vampire",
    "Vagabond",
    "Baron",
    "Obelisk",
    "Baseball Card",
    "Ancient Joker",
    "Campfire",
    "Blueprint",
    "Wee Joker",
    "Hit the Road",
    "The Duo",
    "The Trio",
    "The Family",
    "The Order",
    "The Tribe",
    "Invisible Joker",
    "Brainstorm",
    "Drivers License",
    "Burnt Joker"
};

std::vector<std::string> RARE_JOKERS = {
    "DNA",
    "Vagabond",
    "Baron",
    "Obelisk",
    "Baseball Card",
    "Ancient Joker",
    "Campfire",
    "Blueprint",
    "Wee Joker",
    "Hit the Road",
    "The Duo",
    "The Trio",
    "The Family",
    "The Order",
    "The Tribe",
    "Stuntman",
    "Invisible Joker",
    "Brainstorm",
    "Drivers License",
    "Burnt Joker"
};

std::vector<std::string> LEGENDARY_JOKERS = {
    "Canio",
    "Triboulet",
    "Yorick",
    "Chicot",
    "Perkeo"
};

std::vector<std::string> VOUCHERS = {
    "Overstock",
    "Overstock Plus",
    "Clearance Sale",
    "Liquidation",
    "Hone",
    "Glow Up",
    "Reroll Surplus",
    "Reroll Glut",
    "Crystal Ball",
    "Omen Globe",
    "Telescope",
    "Observatory",
    "Grabber",
    "Nacho Tong",
    "Wasteful",
    "Recyclomancy",
    "Tarot Merchant",
    "Tarot Tycoon",
    "Planet Merchant",
    "Planet Tycoon",
    "Seed Money",
    "Money Tree",
    "Blank",
    "Antimatter",
    "Magic Trick",
    "Illusion",
    "Hieroglyph",
    "Petroglyph",
    "Director's Cut",
    "Retcon",
    "Paint Brush",
    "Palette"
};

std::vector<std::string> SPECTRALS = {
    "Familiar",
    "Grim",
    "Incantation",
    "Talisman",
    "Aura",
    "Wraith",
    "Sigil",
    "Ouija",
    "Ectoplasm",
    "Immolate",
    "Ankh",
    "Deja Vu",
    "Hex",
    "Trance",
    "Medium",
    "Cryptid",
    "RETRY",
    "RETRY"
};

std::vector<std::string> TAGS = {
    "Uncommon Tag",
    "Rare Tag",
    "Negative Tag",
    "Foil Tag",
    "Holographic Tag",
    "Polychrome Tag",
    "Investment Tag",
    "Voucher Tag",
    "Boss Tag",
    "Standard Tag",
    "Charm Tag",
    "Meteor Tag",
    "Buffoon Tag",
    "Handy Tag",
    "Garbage Tag",
    "Ethereal Tag",
    "Coupon Tag",
    "Double Tag",
    "Juggle Tag",
    "D6 Tag",
    "Top-up Tag",
    "Speed Tag",
    "Orbital Tag",
    "Economy Tag"
};

std::vector<std::string> BOSSES = {
    "The Arm",
    "The Club",
    "The Eye",
    "Amber Acorn",
    "Cerulean Bell",
    "Crimson Heart",
    "Verdant Leaf",
    "Violet Vessel",
    "The Fish",
    "The Flint",
    "The Goad",
    "The Head",
    "The Hook",
    "The House",
    "The Manacle",
    "The Mark",
    "The Mouth",
    "The Needle",
    "The Ox",
    "The Pillar",
    "The Plant",
    "The Psychic",
    "The Serpent",
    "The Tooth",
    "The Wall",
    "The Water",
    "The Wheel",
    "The Window"
};