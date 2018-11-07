#include "Party.h"
#include "Encounter.h"
#include "GeneratorUtilities.h"

using namespace GeneratorUtilities;

const float Party::UPPER_XP_MODIFIER = 1.25f;
const float Party::LOWER_XP_MODIFIER = 0.75f;

bool Party::addAdventurer(const uint32_t& level)
{
    // Only add an adventurer when the level is valid.
    if (level >= 1 && level <= 20)
    {
        const auto currentAdventurers = mAdventurerMap[level];
        mAdventurerMap[level] = currentAdventurers + 1;
        calculateDesiredXp();
        return true;
    }
    return false;
}

bool Party::removeAdventurer(const uint32_t& level)
{
    // Only remove an adventurer when the level is valid.
    if (level >= 1 && level <= 20)
    {
        const auto currentAdventurers = mAdventurerMap[level];
        // If we don't have an adventurer 
        if (currentAdventurers != 0)
        {
            mAdventurerMap[level] = currentAdventurers - 1;
            calculateDesiredXp();
            return true;
        }
    }
    return false;
}

uint32_t Party::getNumAdventurers() const
{
    auto numAdventurers = 0;

    for (const auto& adventurers : mAdventurerMap)
    {
        numAdventurers += adventurers.second;
    }

    return numAdventurers;
}

uint32_t Party::getNumAdventurers(const uint32_t& level) const
{
    if (mAdventurerMap.count(level) != 0)
    {
        return mAdventurerMap.at(level);
    }

    return 0;
}

uint32_t Party::getDesiredXp(const GeneratorUtilities::Difficulty& difficulty) const
{
    switch (difficulty)
    {
    case Easy: return mDesiredXpMap.at(Easy);
    case Medium: return mDesiredXpMap.at(Medium);
    case Hard: return mDesiredXpMap.at(Hard);
    case Deadly: return mDesiredXpMap.at(Deadly);
    default: return 0;
    }
}

uint32_t Party::getLowerDesiredXp(const Difficulty& difficulty) const
{
    switch (difficulty)
    {
    case Easy: return mDesiredLowerXpMap.at(Easy);
    case Medium: return mDesiredLowerXpMap.at(Medium);
    case Hard: return mDesiredLowerXpMap.at(Hard);
    case Deadly: return mDesiredLowerXpMap.at(Deadly);
    default: return 0;
    }
}

uint32_t Party::getUpperDesiredXp(const Difficulty& difficulty) const
{
    switch (difficulty)
    {
    case Easy: return mDesiredUpperXpMap.at(Easy);
    case Medium: return mDesiredUpperXpMap.at(Medium);
    case Hard: return mDesiredUpperXpMap.at(Hard);
    case Deadly: return mDesiredUpperXpMap.at(Deadly);
    default: return 0;
    }
}

void Party::calculateDesiredXp()
{
    mDesiredXpMap[Easy] = getBattleXp(Easy);
    mDesiredXpMap[Medium] = getBattleXp(Medium);
    mDesiredXpMap[Hard] = getBattleXp(Hard);
    mDesiredXpMap[Deadly] = getBattleXp(Deadly);

    mDesiredLowerXpMap[Easy] = static_cast<uint32_t>(mDesiredXpMap[Easy] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Medium] = static_cast<uint32_t>(mDesiredXpMap[Medium] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Hard] = static_cast<uint32_t>(mDesiredXpMap[Hard] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Deadly] = static_cast<uint32_t>(mDesiredXpMap[Deadly] * LOWER_XP_MODIFIER);

    mDesiredUpperXpMap[Easy] = static_cast<uint32_t>(mDesiredXpMap[Easy] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Medium] = static_cast<uint32_t>(mDesiredXpMap[Medium] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Hard] = static_cast<uint32_t>(mDesiredXpMap[Hard] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Deadly] = static_cast<uint32_t>(mDesiredXpMap[Deadly] * UPPER_XP_MODIFIER);
}

uint32_t Party::getBattleXp(const Difficulty& difficulty) const
{
    if (difficulty < Easy || difficulty > Deadly)
    {
        return 0;
    }

    auto desiredXp = 0;

    for (const auto& adventurers : mAdventurerMap)
    {
        desiredXp += GenUtil::getAdventurerXp(adventurers.first, difficulty) * adventurers.second;
    }

    return desiredXp;
}
