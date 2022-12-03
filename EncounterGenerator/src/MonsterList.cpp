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

    CreatureType foundType = CreatureType::INVALID;
    bool hasFoundType = false;

    for(const auto& monsterPair : encounter.getMonsterCrMap())
    {
        auto filteredList = filteredListByCr(monsterPair.first);

        // If we have already found a type, try to match found monsters to that list.
        // If we don't have any monsters that can match though, it gives up.
        if(hasFoundType)
        {
            auto typeMatchedFilteredList = filteredList.filteredListByCreatureType(foundType);
            if(!typeMatchedFilteredList.mMonsters.empty())
            {
                filteredList = typeMatchedFilteredList;
            }
        }

        // We aren't guaranteed to always have monsters of what CR we are looking for. Looking at you non-existent CR 29 monsters.
        // If that happens, just start going downwards until we find something. Or eventually give if we are already at zero.
        auto wantedCr = monsterPair.first;
        while(filteredList.mMonsters.empty() && wantedCr != Cr::Zero)
        {
            wantedCr = static_cast<Cr>(static_cast<int>(wantedCr) - 1);
            filteredList = filteredListByCr(wantedCr);
        }

        auto randomMonster = filteredList.getRandomMonster();
        newEncounter.addMonsters(randomMonster, monsterPair.second);

        hasFoundType = true;
        foundType = randomMonster.getCreatureType();
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
