#include "EncounterGenerator.h"
#include "Party.h"
#include <random>
#include <cassert>
#include <chrono>
#include <numeric>

using namespace DnD;

// Not used anymore, but kept for informative purposes.
const std::vector<float> EncounterGenerator::MONSTER_ENCOUNTER_MODIFIERS = {
    0.5f, // 1 monster w/ large party
    1.0f, // 1 monster
    1.5f, // 2 monsters
    2.0f, // 3-6 monsters
    2.5f, // 7-10 monsters
    3.0f, // 11-14 monsters
    4.0f, // 15+ monsters
    5.0f  // 15+ monsters w/ small party
};

EncounterGenerator::EncounterGenerator(const Party &adventurers, const uint32_t &numUniqueMonsters, const uint32_t& numTotalMonsters) :
    mParty(adventurers),
    mNumUniqueMonsters(numUniqueMonsters),
    mNumTotalMonsters(numTotalMonsters),
    mValidBattles({})
{
    setMinimumMonsterXp();
    setMaximumMonsterXp();
    fillOutEncounters();
}

std::vector<Encounter> EncounterGenerator::getEncounters(const Difficulty& difficulty, uint32_t numBattles) const
{
    auto battles = getAllEncounters(difficulty);

    if(battles.empty() || numBattles == 0)
    {
        return {};
    }

    // Vectorize the battles we will be choosing from.
    std::vector<Encounter> vectorizedBattles;

    for (const auto battle : battles)
    {
        vectorizedBattles.push_back(battle);
    }

    // Create a selection vector that increases from 0 -> total number of battles - 1.
    // Then shuffle it around so we have a pick without replacement vector.
    std::vector<int> selectionVector(battles.size());
    std::iota(std::begin(selectionVector), std::end(selectionVector), 0); // Fill with 0, 1, ..., 99.

    // obtain a time-based seed:
    auto seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(selectionVector.begin(), selectionVector.end(), std::default_random_engine(seed));

    // Create the output battleVector.
    std::vector<Encounter> outputBattles(numBattles);

    // if we have less numBattles than the total num battles, we will never have repeats.
    // If we loop over, just keep filling it so that we always get how many we ask for.
    for(uint32_t i = 0; i < numBattles; i++)
    {
        outputBattles[i] = vectorizedBattles[selectionVector[i%selectionVector.size()]];
    }

    return outputBattles;
}

std::vector<Encounter> EncounterGenerator::getAllEncounters(const Difficulty& difficulty) const
{
    if(mValidBattles.count(difficulty) != 0)
    {
        return mValidBattles.at(difficulty);
    }

    return {};
}

float EncounterGenerator::getXpModifier(const uint32_t& numMonsters) const
{
    const auto numAdventurers = mParty.getNumAdventurers();
    // If we have no characters, no xp can be given.
    if (numAdventurers == 0)
    {
        assert(false);
        return 0;
    }

    // If we have no monsters, no xp can be given.
    if (numMonsters == 0)
    {
        return 0;
    }

    // This approximates the Monster EncounterGenerator Modifier, with more emphasis on balancing monsters vs players.
    auto xpMod = 2.0f - numAdventurers / 4.0f + (numMonsters - 1)*0.2f;
    if(xpMod < 0.5f)
    {
        xpMod = 0.5f;
    }

    return xpMod;
}

Encounter EncounterGenerator::convertMonsterVectorToEncounter(const std::vector<uint32_t>& monsterXpVector)
{
    Encounter encounter;
    // Fill out the list so we can get the desired xp.
    for (auto monsterXp : monsterXpVector)
    {
        auto monsterCr = GeneratorUtilities::getMonsterCr(monsterXp);
        encounter.addMonsters(monsterCr, 1);
    }

    return encounter;
}

std::vector<uint32_t> EncounterGenerator::getValidMonsterXPs(const uint32_t& minXp, const uint32_t& maxXp)
{
    std::vector<uint32_t> validXps;

    for (auto xp : MONSTER_XP_TABLE)
    {
        if (xp >= minXp && xp <= maxXp)
        {
            validXps.push_back(xp);
        }
    }

    return validXps;
}

void EncounterGenerator::setMinimumMonsterXp()
{
    for(const auto & diff : DIFFICULTY_VECTOR)
    {
        mMinimumMonsterXp[diff] = getMinimumMonsterXp(diff);
    }
}

uint32_t EncounterGenerator::getMinimumMonsterXp(const Difficulty& difficulty) const
{
    const auto desiredXp = mParty.getDesiredXp(difficulty);

    if(mNumTotalMonsters == 0)
    {
        return 0;
    }

    const auto lowestXp = desiredXp / mNumTotalMonsters;
    auto lastXp = 0;

    for(auto xp : MONSTER_XP_TABLE)
    {
        if (lowestXp <= xp)
        {
            return lastXp;
        }
        lastXp = xp;
    }

    return 0;
}

void EncounterGenerator::setMaximumMonsterXp()
{
    for (const auto & diff : DIFFICULTY_VECTOR)
    {
        mMaximumMonsterXp[diff] = getMaximumMonsterXp(diff);
    }
}

uint32_t EncounterGenerator::getMaximumMonsterXp(const Difficulty& difficulty) const
{
    const auto desiredXp = mParty.getDesiredXp(difficulty);

    if (mNumTotalMonsters == 0)
    {
        return 0;
    }

    const auto highestXp = desiredXp / getXpModifier(1);
    auto lastXp = 0;

    for (auto xp : MONSTER_XP_TABLE)
    {
        if (xp >= highestXp)
        {
            return lastXp;
        }
        lastXp = xp;
    }

    return lastXp;
}

void EncounterGenerator::fillOutEncounters()
{
    mValidBattles.clear();
    for(const auto& diff : DIFFICULTY_VECTOR)
    {
        std::vector<uint32_t> monsters;
        auto validXps = getValidMonsterXPs(mMinimumMonsterXp[diff], mMaximumMonsterXp[diff]);
        auto lowXp = mParty.getLowerDesiredXp(diff);
        auto desiredXp = mParty.getDesiredXp(diff);
        auto highXp = mParty.getUpperDesiredXp(diff);
        fillOutHelper(monsters, diff, validXps, lowXp, desiredXp, highXp);
    }

}

void EncounterGenerator::fillOutHelper(std::vector<uint32_t>& currentMonsters, const Difficulty& difficulty, const std::vector<uint32_t>& validXps, const uint32_t& lowXp, const uint32_t& desiredXp, const uint32_t& highXp)
{
    // Get the current encounter as it stands.
    const auto encounter = convertMonsterVectorToEncounter(currentMonsters);
    const auto xp = encounter.getEncounterXp() * getXpModifier(static_cast<uint32_t>(currentMonsters.size()));

    // Run some checks to see if we should quit out now.
    const auto tooManyTotalMonsters = currentMonsters.size() > mNumTotalMonsters;
    const auto tooManyUniqueMonsters = encounter.getNumUniqueMonsters() > mNumUniqueMonsters;
    const auto tooMuchXp = xp > highXp;
    if (tooManyTotalMonsters || tooManyUniqueMonsters || tooMuchXp)
    {
        return;
    }

    // See if we are in a valid xp range.
    const auto inXpRange = (xp >= lowXp) && (xp <= highXp);

    // When adding monsters into the map, add them in chunks that must make up at least 20% of allotted xp.
    const auto minXpPerCr = desiredXp / 5;

    // If we are in the correct xp range do some last checks.
    // Ensure that only one battle per set has a unique number of monsters.
    // This stops it from having 3 entries in the table being nearly the same but just one cr off with the same number of monsters.
    if(inXpRange)
    {
        auto uniqueNumberOfMonsters = true;
        const auto testNumMons = encounter.getNumTotalMonsters();

        for(const auto& diffEncounter : mValidBattles[difficulty])
        {
            const auto numSetMons = diffEncounter.getNumTotalMonsters();
            uniqueNumberOfMonsters = uniqueNumberOfMonsters && (testNumMons != numSetMons);
        }

        if(uniqueNumberOfMonsters)
        {
            mValidBattles[difficulty].push_back(encounter);
            return;
        }
    }

    // We are not in a valid state yet, try to add more monsters in.
    for(auto newXp : validXps)
    {
        // Calculate how many monsters should be added in this batch
        auto numNewMonsters = minXpPerCr / newXp;
        if (numNewMonsters == 0) numNewMonsters = 1;

        // Add the monsters in. Recurse. Remove monsters.
        for (uint32_t i = 0; i < numNewMonsters; i++)
        {
            currentMonsters.push_back(newXp);
        }
        fillOutHelper(currentMonsters, difficulty, validXps, lowXp, desiredXp, highXp);
        for (uint32_t i = 0; i < numNewMonsters; i++)
        {
            currentMonsters.pop_back();
        }
    }

}
