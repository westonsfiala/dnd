#pragma once
#include <map>
#include "GeneratorUtilities.h"

class Party
{
public:
    Party() = default;
    Party(const Party& other) = default;
    ~Party() = default;

    bool addAdventurer(const uint32_t& level);
    bool removeAdventurer(const uint32_t& level);

    uint32_t getNumAdventurers() const;
    uint32_t getNumAdventurers(const uint32_t& level) const;

    uint32_t getDesiredXp(const GeneratorUtilities::Difficulty& difficulty) const;
    uint32_t getLowerDesiredXp(const GeneratorUtilities::Difficulty& difficulty) const;
    uint32_t getUpperDesiredXp(const GeneratorUtilities::Difficulty& difficulty) const;

private:

    static const float UPPER_XP_MODIFIER;
    static const float LOWER_XP_MODIFIER;

    void calculateDesiredXp();
    uint32_t getBattleXp(const GeneratorUtilities::Difficulty& difficulty) const;

    std::map<uint32_t, uint32_t> mAdventurerMap;
    std::map<GeneratorUtilities::Difficulty, uint32_t> mDesiredXpMap;
    std::map<GeneratorUtilities::Difficulty, uint32_t> mDesiredLowerXpMap;
    std::map<GeneratorUtilities::Difficulty, uint32_t> mDesiredUpperXpMap;

};

