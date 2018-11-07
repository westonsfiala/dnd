#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include "Party.h"

using namespace GeneratorUtilities;

class Encounter
{
public:
    Encounter(const Party& adventurers, const uint32_t& numMonsters);
    ~Encounter() = default;

    std::map<Cr, uint32_t> getBattle(const Difficulty& difficulty) const;

    std::set<std::map<Cr, uint32_t>> getAllBattles(const Difficulty& difficulty) const;

    static uint32_t getBattleXp(const std::map<Cr, uint32_t>& monsterMap);

private:
    static const std::vector<float> MONSTER_ENCOUNTER_MODIFIERS;

    float getXpModifier(const uint32_t& numMonsters) const;
    static std::map<Cr, uint32_t> getMonsterMap(const std::vector<uint32_t>& monsters);

    void setMinimumMonsterXp();
    uint32_t getMinimumMonsterXp(const Difficulty& difficulty) const;

    void fillOutEncounters();
    void fillOutHelper(std::vector<uint32_t>& currentMonsters, const Difficulty& difficulty);

    Party mParty;
    uint32_t mNumMonsters{};
    uint32_t mNumUniqueMonsters{};
    std::map<Difficulty, uint32_t> mMinimumMonsterXp{};
    std::unordered_map<Difficulty, std::set<std::map<Cr, uint32_t>>> mValidBattles{};
};
