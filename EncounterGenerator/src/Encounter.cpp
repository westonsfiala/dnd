#include "Encounter.h"

#include <string>

using namespace DnD;

Encounter::Encounter()
{
}

void Encounter::addMonsters(Cr cr, uint32_t numMonsters)
{
    mMonsterMap[cr] += numMonsters;
}

void Encounter::removeMonsters(Cr cr, uint32_t numMonsters)
{
    if(mMonsterMap.count(cr) != 0)
    {
        if (mMonsterMap[cr] <= numMonsters)
        {
            mMonsterMap.erase(cr);
        }
        else
        {
            mMonsterMap[cr] -= numMonsters;
        }
    }
}

std::map<Cr, uint32_t> Encounter::getMonsters() const
{
    return mMonsterMap;
}

uint32_t Encounter::getNumUniqueMonsters() const
{
    return static_cast<uint32_t>(mMonsterMap.size());
}

uint32_t Encounter::getNumTotalMonsters() const
{
    auto numMonsters = 0;
    for (const auto& crNumPair : mMonsterMap)
    {
        numMonsters += crNumPair.second;
    }
    return numMonsters;
}

uint32_t Encounter::getEncounterXp() const
{
    auto battleXp = 0;
    for (const auto &monsterGroup : mMonsterMap)
    {
        battleXp += GeneratorUtilities::getMonsterXp(monsterGroup.first) * monsterGroup.second;
    }
    return battleXp;
}

std::string Encounter::toString() const
{
    std::string encounterString = "";
    for (auto monsterPair : mMonsterMap)
    {
        encounterString += std::to_string(monsterPair.second) + " CR " + GeneratorUtilities::toStringCr(monsterPair.first) + " : ";
    }
    // Get rid of the fence post stuff.
    encounterString.pop_back();
    encounterString.pop_back();
    encounterString.pop_back();

    return encounterString;
}

