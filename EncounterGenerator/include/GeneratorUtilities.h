#pragma once
#include <map>
#include <vector>

namespace DnD
{

/**
 * \brief Set difficulties for a battle.
 */
enum class Difficulty
{
    Easy,
    Medium,
    Hard,
    Deadly,
    Insanity,
    INVALID
};

/**
 * \brief Vector of all the difficulties.
 */
static const std::vector<Difficulty> DIFFICULTY_VECTOR = {
    Difficulty::Easy,
    Difficulty::Medium,
    Difficulty::Hard,
    Difficulty::Deadly,
    Difficulty::Insanity
};

/**
 * \brief Battle xp for all adventurer levels 0-20 at easy difficulty.
 */
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

/**
 * \brief Battle xp for all adventurer levels 0-20 at medium difficulty.
 */
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

/**
 * \brief Battle xp for all adventurer levels 0-20 at hard difficulty.
 */
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

/**
 * \brief Battle xp for all adventurer levels 0-20 at deadly difficulty.
 */
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

/**
 * \brief Battle xp for all adventurer levels 0-20 at insanity difficulty.
 */
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

/**
 * \brief Battle xp for all monster CRs from 0-30.
 */
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

/**
 * \brief Allowed CRs for all monsters.
 */
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
    Thirty,
    INVALID
};

/**
 * \brief Allowed Sizes for all monsters.
 */
enum class CreatureSize
{
    Tiny = 0,
    Small,
    Medium,
    Large,
    Huge,
    Gargantuan,
    INVALID
};

/**
 * \brief Allowed Types for all monsters.
 */
enum class CreatureType
{
    Aberration = 0,
    Beast,
    Celestial,
    Construct,
    Dragon,
    Elemental,
    Fey,
    Fiend,
    Giant,
    Humanoid,
    Monstrosity,
    Ooze,
    Plant,
    Undead,
    INVALID
};

class GeneratorUtilities
{
public:
    /**
     * \brief Gets the xp that an adventurer of the given level wants at the given difficulty.
     * \param level Level of the adventurer.
     * \param difficulty Difficulty of the battle.
     * \return XP that the adventurer wants to earn.
     */
    static uint32_t getAdventurerXp(const uint32_t& level, const Difficulty& difficulty);

    /**
     * \brief Gets the xp that a monster of the given CR will reward.
     * \param challenge CR of the monster.
     * \return XP to award for the given CR.
     */
    static uint32_t getMonsterXp(const Cr &challenge);

    /**
     * \brief Gets the CR of a monster from how much xp it awards.
     * \param xp XP of the monster.
     * \return CR of the monster with the given XP reward. If no exact match is found, finds the nearest, by flooring.
     */
    static Cr getMonsterCr(const uint32_t &xp);

    /**
     * \brief Turns the given difficulty into its string representation.
     * \param difficulty Difficult to turn into a string.
     * \return String representation of the difficulty.
     */
    static std::string toStringDifficulty(const Difficulty &difficulty);

    /**
     * \brief Finds the difficulty from the given string.
     * \param difficultyString String representation of a difficulty.
     * \return Difficulty found from the given string. If no match is found, returns INVALID.
     */
    static Difficulty fromStringDifficulty(const std::string &difficultyString);

    /**
     * \brief Turns the given CR into its string representation.
     * \param cr CR to turn into a string.
     * \return String representation of the CR.
     */
    static std::string toStringCr(const Cr &cr);

    /**
     * \brief Finds the CR from the given string.
     * \param crDouble Double representation of a CR. Rounds down to nearest cr.
     * \return Cr found from the given string. If no match is found, returns INVALID.
     */
    static Cr fromDoubleCr(const double &crDouble);

    /**
     * \brief Turns the given Size into its string representation.
     * \param creatureSize Size to turn into a string.
     * \return String representation of the size.
     */
    static std::string toStringCreatureSize(const CreatureSize &creatureSize);

    /**
     * \brief Finds the creature size from the given string.
     * \param creatureSizeString String representation of a creature size.
     * \return Creature size found from the given string. If no match is found, returns INVALID.
     */
    static CreatureSize fromStringCreatureSize(const std::string &creatureSizeString);

    /**
     * \brief Turns the given type into its string representation.
     * \param creatureType Type to turn into a string.
     * \return String representation of the size.
     */
    static std::string toStringCreatureType(const CreatureType &creatureType);

    /**
     * \brief Finds the creature type from the given string.
     * \param creatureTypeString String representation of a creature type.
     * \return Creature type found from the given string. If no match is found, returns INVALID.
     */
    static CreatureType fromStringCreatureType(const std::string &creatureTypeString);

private:
    static std::map<uint32_t, Cr> GeneratorUtilities::generateXpToCrMap();
    static std::map<Cr, uint32_t> GeneratorUtilities::generateCrToXpMap();
};
}
