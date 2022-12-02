#include "Encounter.h"

#include <string>

using namespace DnD;

Encounter::Encounter()
{
}

void Encounter::addMonsters(Cr cr, uint32_t numMonsters)
{
    mMonsterCrMap[cr] += numMonsters;
}

void Encounter::removeMonsters(Cr cr, uint32_t numMonsters)
{
    if(mMonsterCrMap.count(cr) != 0)
    {
        if (mMonsterCrMap[cr] <= numMonsters)
        {
            mMonsterCrMap.erase(cr);
        }
        else
        {
            mMonsterCrMap[cr] -= numMonsters;
        }
    }
}

std::map<Cr, uint32_t> Encounter::getMonsterCrMap() const
{
    return mMonsterCrMap;
}

uint32_t Encounter::getNumUniqueMonsters() const
{
    return static_cast<uint32_t>(mMonsterCrMap.size());
}

uint32_t Encounter::getNumTotalMonsters() const
{
    auto numMonsters = 0;
    for (const auto& crNumPair : mMonsterCrMap)
    {
        numMonsters += crNumPair.second;
    }
    return numMonsters;
}

uint32_t Encounter::getEncounterXp() const
{
    auto battleXp = 0;
    for (const auto &monsterGroup : mMonsterCrMap)
    {
        battleXp += GeneratorUtilities::getMonsterXp(monsterGroup.first) * monsterGroup.second;
    }
    return battleXp;
}

std::string Encounter::toString() const
{
    std::string encounterString = "";
    for (auto monsterPair : mMonsterCrMap)
    {
        encounterString += std::to_string(monsterPair.second) + " CR " + GeneratorUtilities::toStringCr(monsterPair.first) + " : ";
    }
    // Get rid of the fence post stuff.
    encounterString.pop_back();
    encounterString.pop_back();
    encounterString.pop_back();

    return encounterString;
}

