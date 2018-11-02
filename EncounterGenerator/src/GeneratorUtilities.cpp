#include "GeneratorUtilities.h"

using namespace GeneratorUtilities;

const std::unordered_map<uint32_t, cr> GenUtil::xp_to_cr_map = generate_xp_to_cr_map();
const std::unordered_map<cr, uint32_t> GenUtil::cr_to_xp_map = generate_cr_to_xp_map();

uint32_t GenUtil::get_adventurer_xp(const uint32_t& level, const difficulty& difficulty)
{
    // If the level is invalid, return 0
    if (level < 1 || level > 20)
    {
        return 0;
    }

    switch (difficulty)
    {
    case easy: return easy_battle_adventurer_xp[level];
    case medium: return medium_battle_adventurer_xp[level];
    case hard: return hard_battle_adventurer_xp[level];
    case deadly: return deadly_battle_adventurer_xp[level];
    default: return 0;
    }
}

uint32_t GenUtil::get_monster_xp(const cr& challenge)
{
    if(cr_to_xp_map.count(challenge))
    {
        return cr_to_xp_map.at(challenge);
    }

    return 0;
}

cr GenUtil::get_monster_cr(const uint32_t& xp)
{
    if (xp_to_cr_map.count(xp))
    {
        return xp_to_cr_map.at(xp);
    }

    return zero;
}

std::unordered_map<uint32_t, cr> GenUtil::generate_xp_to_cr_map()
{
    std::unordered_map<uint32_t, cr> map;
    for (auto cr_index = 0; cr_index < monster_xp_table.size(); ++cr_index)
    {
        auto xp = monster_xp_table[cr_index];
        map[xp] = static_cast<cr>(cr_index);
    }
    return map;
}

std::unordered_map<cr, uint32_t> GenUtil::generate_cr_to_xp_map()
{
    std::unordered_map<cr, uint32_t> map;
    for (auto cr_index = 0; cr_index < monster_xp_table.size(); ++cr_index)
    {
        auto xp = monster_xp_table[cr_index];
        map[static_cast<cr>(cr_index)] = xp;
    }
    return map;
}
