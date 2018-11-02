#pragma once
#include <vector>
#include <unordered_map>

namespace GeneratorUtilities
{

enum difficulty
{
    easy,
    medium,
    hard,
    deadly
};

static const std::vector<uint32_t> easy_battle_adventurer_xp = {
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

static const std::vector<uint32_t> medium_battle_adventurer_xp = {
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

static const std::vector<uint32_t> hard_battle_adventurer_xp = {
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

static const std::vector<uint32_t> deadly_battle_adventurer_xp = {
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

static const std::vector<uint32_t> monster_xp_table = {
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

enum cr
{
    zero = 0,
    oneeighth,
    onequarter,
    onehalf,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    eleven,
    twelve,
    thirteen,
    fourteen,
    fifteen,
    sixteen,
    seventeen,
    eighteen,
    nineteen,
    twenty,
    twentyone,
    twentytwo,
    twentythree,
    twentyfour,
    twentyfive,
    twentysix,
    twentyseven,
    twentyeight,
    twentynine,
    thirty
};

class GenUtil
{
public:
    static uint32_t GenUtil::get_adventurer_xp(const uint32_t& level, const difficulty& difficulty);
    static uint32_t get_monster_xp(const cr &challenge);
    static cr get_monster_cr(const uint32_t &xp);

private:
    GenUtil() = delete;
    static const std::unordered_map<uint32_t, cr> xp_to_cr_map;
    static const std::unordered_map<cr, uint32_t> cr_to_xp_map;

    static std::unordered_map<uint32_t, cr> generate_xp_to_cr_map();
    static std::unordered_map<cr, uint32_t> generate_cr_to_xp_map();

};




}
