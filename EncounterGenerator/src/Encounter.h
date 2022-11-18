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
    /**
     * \brief Constructs an encounter where you have a group of adventurers and how many unique monsters you will see.
     * \param adventurers A party of adventurers
     * \param numUniqueMonsters How many unique monsters to field
     */
    Encounter(const Party& adventurers, const uint32_t& numUniqueMonsters, const uint32_t& numTotalMonsters);
    ~Encounter() = default;

    std::vector<std::map<Cr, uint32_t>> getBattles(const Difficulty& difficulty, uint32_t numBattles) const;

    std::set<std::map<Cr, uint32_t>> getAllBattles(const Difficulty& difficulty) const;

    static uint32_t getBattleXp(const std::map<Cr, uint32_t>& monsterMap);

private:
    static const std::vector<float> MONSTER_ENCOUNTER_MODIFIERS;

    float getXpModifier(const uint32_t& numMonsters) const;
    static std::map<Cr, uint32_t> getMonsterMap(const std::vector<uint32_t>& monsters);

    static std::vector<uint32_t> getValidMonsterXPs(const uint32_t& minXp, const uint32_t& maxXp);

    void setMinimumMonsterXp();
    uint32_t getMinimumMonsterXp(const Difficulty& difficulty) const;
    void setMaximumMonsterXp();
    uint32_t getMaximumMonsterXp(const Difficulty& difficulty) const;

    void fillOutEncounters();
    void fillOutHelper(std::vector<uint32_t>& currentMonsters, const Difficulty& difficulty, const std::vector<uint32_t>& validXps, const uint32_t& lowXp, const uint32_t& desiredXp, const uint32_t& highXp);

    Party mParty;
    uint32_t mNumUniqueMonsters{};
    uint32_t mNumTotalMonsters{};
    std::map<Difficulty, uint32_t> mMinimumMonsterXp{};
    std::map<Difficulty, uint32_t> mMaximumMonsterXp{};
    std::unordered_map<Difficulty, std::set<std::map<Cr, uint32_t>>> mValidBattles{};
};
