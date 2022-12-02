#include "MonsterList.h"

#include <algorithm>
#include <chrono>
#include <random>

using namespace DnD;

MonsterList::MonsterList()
{
}

void MonsterList::addMonster(const Monster& monster)
{
    mMonsters.push_back(monster);
}

void MonsterList::removeMonster(const Monster& monster)
{
    std::remove_if(mMonsters.begin(), mMonsters.end(), [monster](const Monster& checkMonster) { return monster == checkMonster; });
}

FilledEncounter MonsterList::fillEncounter(const Encounter& encounter) const
{
    FilledEncounter newEncounter;

    for(const auto& monsterPair : encounter.getMonsterCrMap())
    {
        auto filteredList = filteredListByCr(monsterPair.first);
        auto randomMonster = filteredList.getRandomMonster();
        newEncounter.addMonsters(randomMonster, monsterPair.second);
    }

    return newEncounter;
}

std::vector<FilledEncounter> MonsterList::fillEncounters(const std::vector<Encounter>& encounters) const
{
    std::vector<FilledEncounter> filledEncounters;

    for(const auto& encounter : encounters)
    {
        auto filledEncounter = fillEncounter(encounter);
        filledEncounters.push_back(filledEncounter);
    }

    return filledEncounters;
}

MonsterList MonsterList::filteredListByCr(const Cr& cr) const
{
    MonsterList filteredList;

    for(const auto& monster : mMonsters)
    {
        if(monster.getCr() == cr)
        {
            filteredList.addMonster(monster);
        }
    }

    return filteredList;
}

MonsterList MonsterList::filteredListByCreatureType(const CreatureType& creatureType) const
{
    MonsterList filteredList;

    for (const auto& monster : mMonsters)
    {
        if (monster.getCreatureType() == creatureType)
        {
            filteredList.addMonster(monster);
        }
    }

    return filteredList;
}

Monster MonsterList::getRandomMonster()
{
    const auto seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine engine(seed);
    const std::uniform_int_distribution<int> dist(0, static_cast<int>(mMonsters.size()-1));

    return mMonsters[dist(engine)];
}
