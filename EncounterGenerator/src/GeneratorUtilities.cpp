#include "GeneratorUtilities.h"

namespace GeneratorUtilities
{
/**
     * \brief Helper function for generating a map from xp to cr.
     * \return Map from xp to cr.
     */
    std::unordered_map<uint32_t, Cr> generateXpToCrMap()
    {
        std::unordered_map<uint32_t, Cr> map;
        for (auto crIndex = 0; crIndex < MONSTER_XP_TABLE.size(); ++crIndex)
        {
            const auto xp = MONSTER_XP_TABLE[crIndex];
            map[xp] = static_cast<Cr>(crIndex);
        }
        return map;
    }

/**
     * \brief Helper function for generating a map from cr to xp.
     * \return Map from cr to xp.
     */
    std::unordered_map<Cr, uint32_t> generateCrToXpMap()
    {
        std::unordered_map<Cr, uint32_t> map;
        for (auto crIndex = 0; crIndex < MONSTER_XP_TABLE.size(); ++crIndex)
        {
            const auto xp = MONSTER_XP_TABLE[crIndex];
            map[static_cast<Cr>(crIndex)] = xp;
        }
        return map;
    }

    uint32_t getAdventurerXp(const uint32_t& level, const Difficulty& difficulty)
    {
        // If the level is invalid, return 0
        if (level < 1 || level > 20)
        {
            return 0;
        }

        switch (difficulty)
        {
        case Difficulty::Easy: return EASY_BATTLE_ADVENTURER_XP[level];
        case Difficulty::Medium: return MEDIUM_BATTLE_ADVENTURER_XP[level];
        case Difficulty::Hard: return HARD_BATTLE_ADVENTURER_XP[level];
        case Difficulty::Deadly: return DEADLY_BATTLE_ADVENTURER_XP[level];
        case Difficulty::Insanity: return INSANITY_BATTLE_ADVENTURER_XP[level];
        default: return 0;
        }
    }

    uint32_t getMonsterXp(const Cr& challenge)
    {
        static const auto CR_TO_XP_MAP = generateCrToXpMap();
        if (CR_TO_XP_MAP.count(challenge))
        {
            return CR_TO_XP_MAP.at(challenge);
        }

        return 0;
    }

    Cr getMonsterCr(const uint32_t& xp)
    {
        static const auto XP_TO_CR_MAP = generateXpToCrMap();
        if (XP_TO_CR_MAP.count(xp))
        {
            return XP_TO_CR_MAP.at(xp);
        }

        // No exact match was found. Find the closest while flooring.
        for(auto iter = MONSTER_XP_TABLE.rbegin(); iter != MONSTER_XP_TABLE.rend(); ++iter)
        {
            const auto monsterXp = *iter;
            if(monsterXp < xp)
            {
                return getMonsterCr(monsterXp);
            }
        }

        return Cr::Zero;
    }

    std::string toString(const Difficulty& difficulty)
    {
        switch (difficulty)
        {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Medium: return "Medium";
        case Difficulty::Hard: return "Hard";
        case Difficulty::Deadly: return "Deadly";
        case Difficulty::Insanity: return "Insanity";
        default: return "invalid difficulty";
        }
    }

    std::string toString(const Cr& cr)
    {
        switch (cr)
        {
        case Cr::Zero: return "0";
        case Cr::OneEighth: return "1/8";
        case Cr::OneQuarter: return "1/4";
        case Cr::OneHalf: return "1/2";
        case Cr::One:return "1";
        case Cr::Two: return "2";
        case Cr::Three: return "3";
        case Cr::Four: return "4";
        case Cr::Five: return "5";
        case Cr::Six: return "6";
        case Cr::Seven: return "7";
        case Cr::Eight: return "8";
        case Cr::Nine: return "9";
        case Cr::Ten: return "10";
        case Cr::Eleven: return "11";
        case Cr::Twelve: return "12";
        case Cr::Thirteen: return "13";
        case Cr::Fourteen: return "14";
        case Cr::Fifteen: return "15";
        case Cr::Sixteen: return "16";
        case Cr::Seventeen: return "17";
        case Cr::Eighteen: return "18";
        case Cr::Nineteen: return "19";
        case Cr::Twenty: return "20";
        case Cr::TwentyOne: return "21";
        case Cr::TwentyTwo: return "22";
        case Cr::TwentyThree: return "23";
        case Cr::TwentyFour: return "24";
        case Cr::TwentyFive: return "25";
        case Cr::TwentySix: return "26";
        case Cr::TwentySeven: return "27";
        case Cr::TwentyEight: return "28";
        case Cr::TwentyNine: return "29";
        case Cr::Thirty: return "30";
        default: return "invalid cr";
        }
    }
}