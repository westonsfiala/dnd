#pragma once
#include <vector>
#include <unordered_map>

namespace GeneratorUtilities
{

enum class Difficulty
{
    Easy,
    Medium,
    Hard,
    Deadly,
    Insanity
};

static const std::vector<Difficulty> DIFFICULTY_VECTOR = {
    Difficulty::Easy,
    Difficulty::Medium,
    Difficulty::Hard,
    Difficulty::Deadly,
    Difficulty::Insanity
};

static const std::vector<uint32_t> EASY_BATTLE_ADVENTURER_XP = {
    0,
    25,
    50,
    75,
    125,
    250,
    300,
    350,
    450,
    550,
    600,
    800,
    1000,
    1100,
    1250,
    1400,
    1600,
    2000,
    2100,
    2400,
    2800
};

static const std::vector<uint32_t> MEDIUM_BATTLE_ADVENTURER_XP = {
    0,
    50,
    100,
    150,
    250,
    500,
    600,
    750,
    900,
    1100,
    1200,
    1600,
    2000,
    2200,
    2500,
    2800,
    3200,
    3900,
    4200,
    4900,
    5700
};

static const std::vector<uint32_t> HARD_BATTLE_ADVENTURER_XP = {
    0,
    75,
    150,
    225,
    375,
    750,
    900,
    1100,
    1400,
    1600,
    1900,
    2400,
    3000,
    3400,
    3800,
    4300,
    4800,
    5900,
    6300,
    7300,
    8500
};

static const std::vector<uint32_t> DEADLY_BATTLE_ADVENTURER_XP = {
    0,
    100,
    200,
    400,
    500,
    1100,
    1400,
    1700,
    2100,
    2400,
    2800,
    3600,
    4500,
    5100,
    5700,
    6400,
    7200,
    8800,
    9500,
    10900,
    12700
};

static const std::vector<uint32_t> INSANITY_BATTLE_ADVENTURER_XP = {
    0,
    200,
    400,
    800,
    1000,
    2200,
    2800,
    3400,
    4200,
    4800,
    5600,
    7200,
    9000,
    10200,
    11400,
    12800,
    14400,
    17600,
    19000,
    21800,
    25400
};

static const std::vector<uint32_t> MONSTER_XP_TABLE = {
    10,
    25,
    50,
    100,
    200,
    450,
    700,
    1100,
    1800,
    2300,
    2900,
    3900,
    5000,
    5900,
    7200,
    8400,
    10000,
    11500,
    13000,
    15000,
    18000,
    20000,
    22000,
    25000,
    33000,
    41000,
    50000,
    62000,
    75000,
    90000,
    105000,
    120000,
    135000,
    155000
};

enum class Cr
{
    Zero = 0,
    OneEighth,
    OneQuarter,
    OneHalf,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Eleven,
    Twelve,
    Thirteen,
    Fourteen,
    Fifteen,
    Sixteen,
    Seventeen,
    Eighteen,
    Nineteen,
    Twenty,
    TwentyOne,
    TwentyTwo,
    TwentyThree,
    TwentyFour,
    TwentyFive,
    TwentySix,
    TwentySeven,
    TwentyEight,
    TwentyNine,
    Thirty
};

class GenUtil
{
public:
    static uint32_t GenUtil::getAdventurerXp(const uint32_t& level, const Difficulty& difficulty);
    static uint32_t getMonsterXp(const Cr &challenge);
    static Cr getMonsterCr(const uint32_t &xp);
    static std::string toString(const Difficulty &difficulty);
    static std::string toString(const Cr &cr);

private:
    GenUtil() = delete;
    static const std::unordered_map<uint32_t, Cr> XP_TO_CR_MAP;
    static const std::unordered_map<Cr, uint32_t> CR_TO_XP_MAP;

    static std::unordered_map<uint32_t, Cr> generateXpToCrMap();
    static std::unordered_map<Cr, uint32_t> generateCrToXpMap();

};




}
