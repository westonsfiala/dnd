#include "MonsterList.h"

#include <algorithm>

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
