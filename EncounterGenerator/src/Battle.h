#pragma once
#include <map>
#include "Party.h"
#include "Monster.h"

using namespace GeneratorUtilities;

class Battle
{
public:
    Battle();
    ~Battle() = default;

    void addCr(Cr cr);
    void removeCr(Cr cr);

    void addMonster(const Monster &monster);
    void removeMonster(const Monster &monster);

    

    uint32_t getNumMonsters();

    static uint32_t getBattleXp(const std::map<Cr, uint32_t>& monsterMap);

private:
    std::map<Cr, uint32_t> mCrMap;
    std::map<Monster, uint32_t> mMonsterMap;
};

