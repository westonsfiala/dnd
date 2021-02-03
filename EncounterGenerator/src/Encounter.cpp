#include "Encounter.h"
#include "Party.h"
#include <random>
#include <cmath>
#include <cassert>

#include <nlohmann/json.hpp>

using namespace GeneratorUtilities;

const std::vector<float> Encounter::MONSTER_ENCOUNTER_MODIFIERS = {
    0.5f, // 1 monster w/ large party
    1.0f, // 1 monster
    1.5f, // 2 monsters
    2.0f, // 3-6 monsters
    2.5f, // 7-10 monsters
    3.0f, // 11-14 monsters
    4.0f, // 15+ monsters
    5.0f  // 15+ monsters w/ small party
};

Encounter::Encounter(const Party &adventurers, const uint32_t &numUniqueMonsters, const uint32_t& numTotalMonsters) :
    mParty(adventurers),
    mNumUniqueMonsters(numUniqueMonsters),
    mNumTotalMonsters(numTotalMonsters),
    mValidBattles({})
{
    setMinimumMonsterXp();
    setMaximumMonsterXp();
    fillOutEncounters();
}

std::map<Cr, uint32_t> Encounter::getBattle(const Difficulty& difficulty) const
{
    auto battles = getAllBattles(difficulty);

    if(battles.empty())
    {
        return {};
    }

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    const std::uniform_int_distribution<> dis(0, static_cast<int>(battles.size()) - 1);

    const auto index = dis(gen);

    std::vector<std::map<Cr, uint32_t>> vectorizedBattles;

    for(const auto battle : battles)
    {
        vectorizedBattles.push_back(battle);
    }

    return vectorizedBattles.at(index);
}

std::set<std::map<Cr, uint32_t>> Encounter::getAllBattles(const Difficulty& difficulty) const
{
    if(mValidBattles.count(difficulty) != 0)
    {
        return mValidBattles.at(difficulty);
    }

    return {};
}

uint32_t Encounter::getBattleXp(const std::map<Cr, uint32_t>& monsterMap)
{
    auto battleXp = 0;
    for(const auto &monsterGroup : monsterMap)
    {
        battleXp += getMonsterXp(monsterGroup.first) * monsterGroup.second;
    }
    return battleXp;
}

float Encounter::getXpModifier(const uint32_t& numMonsters) const
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

    uint32_t tableIndex;

    // The standard index goes from 1-6.
    switch (numMonsters)
    {
    case 1: // 1 monster
        tableIndex = 1;
        break;
    case 2: // 2 monsters
        tableIndex = 2;
        break;
    case 3: // 3-6 monsters
    case 4:
    case 5:
    case 6:
        tableIndex = 3;
        break;
    case 7: // 7-10 monsters
    case 8:
    case 9:
    case 10:
        tableIndex = 4;
        break;
    case 11: // 11-14 monsters
    case 12:
    case 13:
    case 14:
        tableIndex = 5;
        break;
    default: // 15+ monsters
        tableIndex = 6;
    }

    // If we have few characters, up the modifier.
    if (numAdventurers <= 2)
    {
        tableIndex++;
    }
    // If we have many characters, lower the modifier.
    else if (numAdventurers >= 6)
    {
        tableIndex--;
    }

    // Return the modifier that
    return MONSTER_ENCOUNTER_MODIFIERS.at(tableIndex);
}

std::map<Cr, uint32_t> Encounter::getMonsterMap(const std::vector<uint32_t>& monsters)
{
    std::map<Cr, uint32_t> monsterMap;
    // Fill out the list so we can get the desired xp.
    for (auto monsterXp : monsters)
    {
        auto monsterCr = getMonsterCr(monsterXp);
        monsterMap[monsterCr]++;
    }

    return monsterMap;
}

std::vector<uint32_t> Encounter::getValidMonsterXPs ( const uint32_t& minXp, const uint32_t& maxXp )
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

void Encounter::setMinimumMonsterXp()
{
    for(const auto & diff : DIFFICULTY_VECTOR)
    {
        mMinimumMonsterXp[diff] = getMinimumMonsterXp(diff);
    }
}

uint32_t Encounter::getMinimumMonsterXp(const Difficulty& difficulty) const
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

void Encounter::setMaximumMonsterXp()
{
    for (const auto & diff : DIFFICULTY_VECTOR)
    {
        mMaximumMonsterXp[diff] = getMaximumMonsterXp(diff);
    }
}

uint32_t Encounter::getMaximumMonsterXp(const Difficulty& difficulty) const
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

    return 0;
}

void Encounter::fillOutEncounters()
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

void Encounter::fillOutHelper(std::vector<uint32_t>& currentMonsters, const Difficulty& difficulty, const std::vector<uint32_t>& validXps, const uint32_t& lowXp, const uint32_t& desiredXp, const uint32_t& highXp)
{
    // Get the monster map.
    const auto monsterMap = getMonsterMap(currentMonsters);
    const auto xp = getBattleXp(monsterMap) * getXpModifier(static_cast<uint32_t>(currentMonsters.size()));

    // Run some checks to see if we should quit out now.
    const auto tooManyTotalMonsters = currentMonsters.size() > mNumTotalMonsters;
    const auto tooManyUniqueMonsters = monsterMap.size() > mNumUniqueMonsters;
    const auto tooMuchXp = xp > highXp;
    if (tooManyTotalMonsters || tooManyUniqueMonsters || tooMuchXp)
    {
        return;
    }

    // See if we are in a valid xp range.
    const auto inXpRange = (xp >= lowXp) && (xp <= highXp);

    // When adding monsters into the map, add them in chunks that must make up at least 20% of allotted xp.
    const auto minXpPerCr = desiredXp / 5;

    // If we have the correct number of monsters and it is in range, success!
    if(inXpRange)
    {
        mValidBattles[difficulty].insert(monsterMap);
        return;
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
