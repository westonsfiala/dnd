#include "GeneratorUtilities.h"

#include <map>

namespace DnD
{
/**
     * \brief Helper function for generating a map from xp to cr.
     * \return Map from xp to cr.
     */
    std::map<uint32_t, Cr> GeneratorUtilities::generateXpToCrMap()
    {
        static std::map<uint32_t, Cr> map;
        if (map.empty())
        {
            for (auto crIndex = 0; crIndex < MONSTER_XP_TABLE.size(); ++crIndex)
            {
                const auto xp = MONSTER_XP_TABLE[crIndex];
                map[xp] = static_cast<Cr>(crIndex);
            }
        }
        return map;
    }

    /**
     * \brief Helper function for generating a map from cr to xp.
     * \return Map from cr to xp.
     */
    std::map<Cr, uint32_t> GeneratorUtilities::generateCrToXpMap()
    {
        static std::map<Cr, uint32_t> map;
        if (map.empty())
        {
            for (auto crIndex = 0; crIndex < MONSTER_XP_TABLE.size(); ++crIndex)
            {
                const auto xp = MONSTER_XP_TABLE[crIndex];
                map[static_cast<Cr>(crIndex)] = xp;
            }
        }
        return map;
    }

    uint32_t GeneratorUtilities::getAdventurerXp(const uint32_t& level, const Difficulty& difficulty)
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

    uint32_t GeneratorUtilities::getMonsterXp(const Cr& challenge)
    {
        static const auto CR_TO_XP_MAP = generateCrToXpMap();
        if (CR_TO_XP_MAP.count(challenge))
        {
            return CR_TO_XP_MAP.at(challenge);
        }

        return 0;
    }

    Cr GeneratorUtilities::getMonsterCr(const uint32_t& xp)
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

    std::string GeneratorUtilities::toStringDifficulty(const Difficulty& difficulty)
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

    Difficulty GeneratorUtilities::fromStringDifficulty(const std::string& difficultyString)
    {
        if(difficultyString == "Easy")
        {
            return Difficulty::Easy;
        }
        if (difficultyString == "Medium")
        {
            return Difficulty::Medium;
        }
        if (difficultyString == "Hard")
        {
            return Difficulty::Hard;
        }
        if (difficultyString == "Deadly")
        {
            return Difficulty::Deadly;
        }
        if (difficultyString == "Insanity")
        {
            return Difficulty::Insanity;
        }
        return Difficulty::INVALID;
    }

    std::string GeneratorUtilities::toStringCr(const Cr& cr)
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

    Cr GeneratorUtilities::fromDoubleCr(const double& crDouble)
    {
        if (crDouble <= 0)
        {
            return Cr::Zero;
        }
        if (crDouble <= 0.125)
        {
            return Cr::OneEighth;
        }
        if (crDouble <= 0.25)
        {
            return Cr::OneQuarter;
        }
        if (crDouble <= 0.5)
        {
            return Cr::OneHalf;
        }
        if (crDouble <= 1)
        {
            return Cr::One;
        }
        if (crDouble <= 2)
        {
            return Cr::Two;
        }
        if (crDouble <= 3)
        {
            return Cr::Three;
        }
        if (crDouble <= 4)
        {
            return Cr::Four;
        }
        if (crDouble <= 5)
        {
            return Cr::Five;
        }
        if (crDouble <= 6)
        {
            return Cr::Six;
        }
        if (crDouble <= 7)
        {
            return Cr::Seven;
        }
        if (crDouble <= 8)
        {
            return Cr::Eight;
        }
        if (crDouble <= 9)
        {
            return Cr::Nine;
        }
        if (crDouble <= 10)
        {
            return Cr::Ten;
        }
        if (crDouble <= 11)
        {
            return Cr::Eleven;
        }
        if (crDouble <= 12)
        {
            return Cr::Twelve;
        }
        if (crDouble <= 13)
        {
            return Cr::Thirteen;
        }
        if (crDouble <= 14)
        {
            return Cr::Fourteen;
        }
        if (crDouble <= 15)
        {
            return Cr::Fifteen;
        }
        if (crDouble <= 16)
        {
            return Cr::Sixteen;
        }
        if (crDouble <= 17)
        {
            return Cr::Seventeen;
        }
        if (crDouble <= 18)
        {
            return Cr::Eighteen;
        }
        if (crDouble <= 19)
        {
            return Cr::Nineteen;
        }
        if (crDouble <= 20)
        {
            return Cr::Twenty;
        }
        if (crDouble <= 21)
        {
            return Cr::TwentyOne;
        }
        if (crDouble <= 22)
        {
            return Cr::TwentyTwo;
        }
        if (crDouble <= 23)
        {
            return Cr::TwentyThree;
        }
        if (crDouble <= 24)
        {
            return Cr::TwentyFour;
        }
        if (crDouble <= 25)
        {
            return Cr::TwentyFive;
        }
        if (crDouble <= 26)
        {
            return Cr::TwentySix;
        }
        if (crDouble <= 27)
        {
            return Cr::TwentySeven;
        }
        if (crDouble <= 28)
        {
            return Cr::TwentyEight;
        }
        if (crDouble <= 29)
        {
            return Cr::TwentyNine;
        }
        if (crDouble <= 30)
        {
            return Cr::Thirty;
        }
        return Cr::INVALID;
    }

    std::string GeneratorUtilities::toStringCreatureSize(const CreatureSize& creatureSize)
    {
        switch (creatureSize)
        {
        case CreatureSize::Tiny: return "Tiny";
        case CreatureSize::Small: return "Small";
        case CreatureSize::Medium: return "Medium";
        case CreatureSize::Large: return "Large";
        case CreatureSize::Huge: return "Huge";
        case CreatureSize::Gargantuan: return "Gargantuan";
        default: return "Invalid Creature Size";
        }
    }

    CreatureSize GeneratorUtilities::fromStringCreatureSize(const std::string& creatureSizeString)
    {
        if (creatureSizeString == "Tiny")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Small")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Medium")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Large")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Huge")
        {
            return CreatureSize::Tiny;
        }
        if (creatureSizeString == "Gargantuan")
        {
            return CreatureSize::Tiny;
        }
        return CreatureSize::INVALID;
    }

    std::string GeneratorUtilities::toStringCreatureType(const CreatureType& creatureType)
    {
        switch (creatureType)
        {
        case CreatureType::Aberration: return "Aberration";
        case CreatureType::Beast: return "Beast";
        case CreatureType::Celestial: return "Celestial";
        case CreatureType::Construct: return "Construct";
        case CreatureType::Dragon: return "Dragon";
        case CreatureType::Elemental: return "Elemental";
        case CreatureType::Fey: return "Fey";
        case CreatureType::Fiend: return "Fiend";
        case CreatureType::Giant: return "Giant";
        case CreatureType::Humanoid: return "Humanoid";
        case CreatureType::Monstrosity: return "Monstrosity";
        case CreatureType::Ooze: return "Ooze";
        case CreatureType::Plant: return "Plant";
        case CreatureType::Undead: return "Undead";
        default: return "Invalid Creature Type";
        }
    }

    CreatureType GeneratorUtilities::fromStringCreatureType(const std::string& creatureTypeString)
    {
        if (creatureTypeString == "Aberration")
        {
            return CreatureType::Aberration;
        }
        if (creatureTypeString == "Beast")
        {
            return CreatureType::Beast;
        }
        if (creatureTypeString == "Celestial")
        {
            return CreatureType::Celestial;
        }
        if (creatureTypeString == "Construct")
        {
            return CreatureType::Construct;
        }
        if (creatureTypeString == "Dragon")
        {
            return CreatureType::Dragon;
        }
        if (creatureTypeString == "Elemental")
        {
            return CreatureType::Elemental;
        }
        if (creatureTypeString == "Fey")
        {
            return CreatureType::Fey;
        }
        if (creatureTypeString == "Fiend")
        {
            return CreatureType::Fiend;
        }
        if (creatureTypeString == "Giant")
        {
            return CreatureType::Giant;
        }
        if (creatureTypeString == "Humanoid")
        {
            return CreatureType::Humanoid;
        }
        if (creatureTypeString == "Monstrosity")
        {
            return CreatureType::Monstrosity;
        }
        if (creatureTypeString == "Ooze")
        {
            return CreatureType::Ooze;
        }
        if (creatureTypeString == "Plant")
        {
            return CreatureType::Plant;
        }
        if (creatureTypeString == "Undead")
        {
            return CreatureType::Undead;
        }
        return CreatureType::INVALID;
    }
}
