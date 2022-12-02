#pragma once
#include "Encounter.h"
#include "Monster.h"

using namespace DnD;

class MonsterList
{
public:
    MonsterList();
    ~MonsterList() = default;

    void addMonster(const Monster& monster);
    void removeMonster(const Monster& monster);

private:

    MonsterList filteredListByCr(const Cr& cr) const;
    MonsterList filteredListByCreatureType(const CreatureType& cr) const;

    Monster getRandomMonster();

    std::vector<Monster> mMonsters;
};
