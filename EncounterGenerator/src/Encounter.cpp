#include "Encounter.h"
#include "Party.h"
#include <random>
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

Encounter::Encounter(const Party &adventurers, const uint32_t &num_monsters) :
    mParty(adventurers),
    mNumMonsters(num_monsters),
    mNumUniqueMonsters(static_cast<uint32_t>(round(log2(mNumMonsters)))),
    mValidBattles({})
{
    setMinimumMonsterXp();
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
        battleXp += GenUtil::getMonsterXp(monsterGroup.first) * monsterGroup.second;
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
    case 7: // 7-8 monsters
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
        auto monsterCr = GenUtil::getMonsterCr(monsterXp);
        monsterMap[monsterCr]++;
    }

    return monsterMap;
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

    if(mNumMonsters == 0)
    {
        return 0;
    }

    const auto lowestXp = desiredXp / mNumMonsters;
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

void Encounter::fillOutEncounters()
{
    mValidBattles.clear();
    for(const auto& diff : DIFFICULTY_VECTOR)
    {
        std::vector<uint32_t> monsters;
        fillOutHelper(monsters, diff);
    }
}

void Encounter::fillOutHelper(std::vector<uint32_t>& currentMonsters, const Difficulty& difficulty)
{
    // Get the monster map.
    const auto monsterMap = getMonsterMap(currentMonsters);
    const auto xp = getBattleXp(monsterMap) * getXpModifier(static_cast<uint32_t>(currentMonsters.size()));

    // Get the lower and upper bounds on xp.
    const auto lowDesired = mParty.getLowerDesiredXp(difficulty);
    const auto upperDesired = mParty.getUpperDesiredXp(difficulty);

    // Get the checks that need to be true to add the monsters into the list.
    const auto correctNumMonsters = currentMonsters.size() <= mNumMonsters;
    const auto inXpRange = xp >= lowDesired && xp <= upperDesired;
    const auto correctUniqueMonsters = monsterMap.size() <= mNumUniqueMonsters;

    // If we have the correct number of monsters and it is in range, success!
    if(correctNumMonsters && inXpRange && correctUniqueMonsters)
    {
        mValidBattles[difficulty].insert(monsterMap);
    }
    else if (currentMonsters.size() < mNumMonsters)
    {
        // Go through all of the xp tables and get the monsters.
        for(auto newXp : MONSTER_XP_TABLE)
        {
            // If the current xp + new monster xp is over the upper_desired range, don't even try to add it in.
            // Also, don't try to add in monsters that are lower than the minimum xp threshold.
            if (xp + newXp < upperDesired && newXp >= mMinimumMonsterXp[difficulty])
            {
                currentMonsters.push_back(newXp);
                fillOutHelper(currentMonsters, difficulty);
                currentMonsters.pop_back();
            }
        }
    }

}
