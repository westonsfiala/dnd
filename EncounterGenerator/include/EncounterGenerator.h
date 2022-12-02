#pragma once
#include <vector>
#include <map>

#include "Encounter.h"
#include "Party.h"

using namespace DnD;

class EncounterGenerator
{
public:
    /**
     * \brief Constructs an encounter where you have a group of adventurers and how many unique monsters you will see.
     * \param adventurers A party of adventurers.
     * \param numUniqueMonsters How many unique monsters to field.
     * \param numTotalMonsters Maximum number of monsters to field.
     */
    EncounterGenerator(const Party& adventurers, const uint32_t& numUniqueMonsters, const uint32_t& numTotalMonsters);
    ~EncounterGenerator() = default;

    std::vector<Encounter> getEncounters(const Difficulty& difficulty, uint32_t numBattles) const;

    std::vector<Encounter> getAllEncounters(const Difficulty& difficulty) const;

private:
    static const std::vector<float> MONSTER_ENCOUNTER_MODIFIERS;

    float getXpModifier(const uint32_t& numMonsters) const;
    static Encounter convertMonsterVectorToEncounter(const std::vector<uint32_t>& monsterXpVector);

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
    std::map<Difficulty, std::vector<Encounter>> mValidBattles{};
};
