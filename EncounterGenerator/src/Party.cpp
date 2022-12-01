#include "Party.h"
#include "EncounterGenerator.h"
#include "GeneratorUtilities.h"

using namespace DnD;

constexpr float Party::UPPER_XP_MODIFIER = 1.25f;
constexpr float Party::LOWER_XP_MODIFIER = 0.75f;

bool Party::addAdventurer(const uint32_t& level, const uint32_t& count)
{
    // Only add an adventurer when the level is valid.
    if (level >= 1 && level <= 20)
    {
        const auto currentAdventurers = mAdventurerMap[level];
        mAdventurerMap[level] = currentAdventurers + count;
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

uint32_t Party::getDesiredXp(const Difficulty& difficulty) const
{
    if(mDesiredXpMap.count(difficulty) != 0)
    {
        return mDesiredXpMap.at(difficulty);
    }

    return 0;
}

uint32_t Party::getLowerDesiredXp(const Difficulty& difficulty) const
{
    if (mDesiredXpMap.count(difficulty) != 0)
    {
        return static_cast<uint32_t>(mDesiredXpMap.at(difficulty) * LOWER_XP_MODIFIER);
    }

    return 0;
}

uint32_t Party::getUpperDesiredXp(const Difficulty& difficulty) const
{
    if (mDesiredXpMap.count(difficulty) != 0)
    {
        return static_cast<uint32_t>(mDesiredXpMap.at(difficulty) * UPPER_XP_MODIFIER);
    }

    return 0;
}

void Party::calculateDesiredXp()
{
    for(const auto& diff : DIFFICULTY_VECTOR)
    {
        mDesiredXpMap[diff] = getBattleXp(diff);
    }
}

uint32_t Party::getBattleXp(const Difficulty& difficulty) const
{
    if (difficulty < Difficulty::Easy || difficulty > Difficulty::Insanity)
    {
        return 0;
    }

    auto desiredXp = 0;

    for (const auto& adventurers : mAdventurerMap)
    {
        // For every level that we have adventurers, get their desired xp and multiply it by the number of adventurers. 
        desiredXp += getAdventurerXp(adventurers.first, difficulty) * adventurers.second;
    }

    return desiredXp;
}
