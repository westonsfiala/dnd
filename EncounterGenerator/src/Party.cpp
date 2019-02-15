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
    case Difficulty::Easy: return mDesiredXpMap.at(Difficulty::Easy);
    case Difficulty::Medium: return mDesiredXpMap.at(Difficulty::Medium);
    case Difficulty::Hard: return mDesiredXpMap.at(Difficulty::Hard);
    case Difficulty::Deadly: return mDesiredXpMap.at(Difficulty::Deadly);
    case Difficulty::Insanity: return mDesiredXpMap.at(Difficulty::Insanity);
    default: return 0;
    }
}

uint32_t Party::getLowerDesiredXp(const Difficulty& difficulty) const
{
    switch (difficulty)
    {
    case Difficulty::Easy: return mDesiredLowerXpMap.at(Difficulty::Easy);
    case Difficulty::Medium: return mDesiredLowerXpMap.at(Difficulty::Medium);
    case Difficulty::Hard: return mDesiredLowerXpMap.at(Difficulty::Hard);
    case Difficulty::Deadly: return mDesiredLowerXpMap.at(Difficulty::Deadly);
    case Difficulty::Insanity: return mDesiredLowerXpMap.at(Difficulty::Insanity);
    default: return 0;
    }
}

uint32_t Party::getUpperDesiredXp(const Difficulty& difficulty) const
{
    switch (difficulty)
    {
    case Difficulty::Easy: return mDesiredUpperXpMap.at(Difficulty::Easy);
    case Difficulty::Medium: return mDesiredUpperXpMap.at(Difficulty::Medium);
    case Difficulty::Hard: return mDesiredUpperXpMap.at(Difficulty::Hard);
    case Difficulty::Deadly: return mDesiredUpperXpMap.at(Difficulty::Deadly);
    case Difficulty::Insanity: return mDesiredUpperXpMap.at(Difficulty::Insanity);
    default: return 0;
    }
}

void Party::calculateDesiredXp()
{
    mDesiredXpMap[Difficulty::Easy] = getBattleXp(Difficulty::Easy);
    mDesiredXpMap[Difficulty::Medium] = getBattleXp(Difficulty::Medium);
    mDesiredXpMap[Difficulty::Hard] = getBattleXp(Difficulty::Hard);
    mDesiredXpMap[Difficulty::Deadly] = getBattleXp(Difficulty::Deadly);
    mDesiredXpMap[Difficulty::Insanity] = getBattleXp(Difficulty::Insanity);

    mDesiredLowerXpMap[Difficulty::Easy] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Easy] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Difficulty::Medium] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Medium] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Difficulty::Hard] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Hard] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Difficulty::Deadly] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Deadly] * LOWER_XP_MODIFIER);
    mDesiredLowerXpMap[Difficulty::Insanity] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Insanity] * LOWER_XP_MODIFIER);

    mDesiredUpperXpMap[Difficulty::Easy] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Easy] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Difficulty::Medium] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Medium] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Difficulty::Hard] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Hard] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Difficulty::Deadly] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Deadly] * UPPER_XP_MODIFIER);
    mDesiredUpperXpMap[Difficulty::Insanity] = static_cast<uint32_t>(mDesiredXpMap[Difficulty::Insanity] * UPPER_XP_MODIFIER);
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
        desiredXp += GenUtil::getAdventurerXp(adventurers.first, difficulty) * adventurers.second;
    }

    return desiredXp;
}
