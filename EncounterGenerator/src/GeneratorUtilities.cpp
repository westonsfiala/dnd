#include "GeneratorUtilities.h"

using namespace GeneratorUtilities;

const std::unordered_map<uint32_t, Cr> GenUtil::XP_TO_CR_MAP = generateXpToCrMap();
const std::unordered_map<Cr, uint32_t> GenUtil::CR_TO_XP_MAP = generateCrToXpMap();

uint32_t GenUtil::getAdventurerXp(const uint32_t& level, const Difficulty& difficulty)
{
    // If the level is invalid, return 0
    if (level < 1 || level > 20)
    {
        return 0;
    }

    switch (difficulty)
    {
    case Easy: return EASY_BATTLE_ADVENTURER_XP[level];
    case Medium: return MEDIUM_BATTLE_ADVENTURER_XP[level];
    case Hard: return HARD_BATTLE_ADVENTURER_XP[level];
    case Deadly: return DEADLY_BATTLE_ADVENTURER_XP[level];
    default: return 0;
    }
}

uint32_t GenUtil::getMonsterXp(const Cr& challenge)
{
    if(CR_TO_XP_MAP.count(challenge))
    {
        return CR_TO_XP_MAP.at(challenge);
    }

    return 0;
}

Cr GenUtil::getMonsterCr(const uint32_t& xp)
{
    if (XP_TO_CR_MAP.count(xp))
    {
        return XP_TO_CR_MAP.at(xp);
    }

    return Zero;
}

std::string GenUtil::toString(const Difficulty& difficulty)
{
    switch(difficulty)
    {
    case Easy: return "Easy";
    case Medium: return "Medium";
    case Hard: return "Hard";
    case Deadly: return "Deadly";
    default: return "invalid difficulty";
    }
}

std::string GenUtil::toString(const Cr& cr)
{
    switch(cr)
    {
    case Zero: return "0";
    case OneEighth: return "1/8";
    case OneQuarter: return "1/4";
    case OneHalf: return "1/2";
    case One:return "1";
    case Two: return "2";
    case Three: return "3";
    case Four: return "4";
    case Five: return "5";
    case Six: return "6";
    case Seven: return "7";
    case Eight: return "8";
    case Nine: return "9";
    case Ten: return "10";
    case Eleven: return "11";
    case Twelve: return "12";
    case Thirteen: return "13";
    case Fourteen: return "14";
    case Fifteen: return "15";
    case Sixteen: return "16";
    case Seventeen: return "17";
    case Eighteen: return "18";
    case Nineteen: return "19";
    case Twenty: return "20";
    case TwentyOne: return "21";
    case TwentyTwo: return "22";
    case TwentyThree: return "23";
    case TwentyFour: return "24";
    case TwentyFive: return "25";
    case TwentySix: return "26";
    case TwentySeven: return "27";
    case TwentyEight: return "28";
    case TwentyNine: return "29";
    case Thirty: return "30";
    default: return "invalid cr";
    }
}

std::unordered_map<uint32_t, Cr> GenUtil::generateXpToCrMap()
{
    std::unordered_map<uint32_t, Cr> map;
    for (auto cr_index = 0; cr_index < MONSTER_XP_TABLE.size(); ++cr_index)
    {
        auto xp = MONSTER_XP_TABLE[cr_index];
        map[xp] = static_cast<Cr>(cr_index);
    }
    return map;
}

std::unordered_map<Cr, uint32_t> GenUtil::generateCrToXpMap()
{
    std::unordered_map<Cr, uint32_t> map;
    for (auto cr_index = 0; cr_index < MONSTER_XP_TABLE.size(); ++cr_index)
    {
        auto xp = MONSTER_XP_TABLE[cr_index];
        map[static_cast<Cr>(cr_index)] = xp;
    }
    return map;
}
