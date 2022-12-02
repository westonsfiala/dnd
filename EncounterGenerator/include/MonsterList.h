#pragma once
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

    std::vector<Monster> mMonsters;
};
