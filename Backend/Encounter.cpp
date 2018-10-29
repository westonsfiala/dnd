#include "stdafx.h"
#include "Encounter.h"
#include "Party.h"
#include "Tables.h"
#include <random>
#include <cassert>

const std::vector<float> Encounter::monster_encounter_modifiers = {
    0.5f, // 1 monster w/ large party
    1.0f, // 1 monster
    1.5f, // 2 monsters
    2.0f, // 3-6 monsters
    2.5f, // 7-10 monsters
    3.0f, // 11-14 monsters
    4.0f, // 15+ monsters
    5.0f  // 15+ monsters with large party
};

Encounter::Encounter(const Party &adventurers, const uint32_t &num_monsters) :
    m_party_(adventurers),
    m_num_monsters_(num_monsters),
    m_num_unique_monsters_(static_cast<uint32_t>(round(log2(m_num_monsters_)))),
    m_valid_battles_({})
{
    set_minimum_monster_xp();
    fill_out_encounters();
}

std::map<float, uint32_t> Encounter::get_battle(const difficulty& difficulty) const
{
    auto battles = get_all_battles(difficulty);

    if(battles.empty())
    {
        return {};
    }

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    const std::uniform_int_distribution<> dis(0, static_cast<int>(battles.size()) - 1);

    const auto index = dis(gen);

    std::vector<std::map<float, uint32_t>> vectorized_battles;

    for(const auto battle : battles)
    {
        vectorized_battles.push_back(battle);
    }

    return vectorized_battles.at(index);
}

std::set<std::map<float, uint32_t>> Encounter::get_all_battles(const difficulty& difficulty) const
{
    if(m_valid_battles_.count(difficulty) != 0)
    {
        return m_valid_battles_.at(difficulty);
    }

    return {};
}

uint32_t Encounter::get_battle_xp(const std::map<float, uint32_t>& monster_map)
{
    auto battle_xp = 0;
    for(const auto &monster_group : monster_map)
    {
        battle_xp += get_monster_xp(monster_group.first) * monster_group.second;
    }
    return battle_xp;
}

uint32_t Encounter::get_monster_xp(const float& monster_cr)
{
    // See if this is a valid monster cr.
    if(cr_to_xp_map.count(monster_cr) != 0)
    {
        return cr_to_xp_map.at(monster_cr);
    }
    
    // Nope, return 0;
    assert(false);
    return 0;
}

float Encounter::get_monster_cr(const uint32_t& monster_xp)
{
    // See if this is a valid monster xp.
    if (xp_to_cr_map.count(monster_xp) != 0)
    {
        return xp_to_cr_map.at(monster_xp);
    }

    // Nope, return 0;
    assert(false);
    return 0;
}

float Encounter::get_xp_modifier(const uint32_t& num_monsters) const
{
    const auto num_adventurers = m_party_.get_num_adventurers();
    // If we have no characters, no xp can be given.
    if (num_adventurers == 0)
    {
        assert(false);
        return 0;
    }

    // If we have no monsters, no xp can be given.
    if (num_monsters == 0)
    {
        return 0;
    }

    uint32_t table_index;

    // The standard indexs go from 1-6.
    switch (num_monsters)
    {
    case 1: // 1 monster
        table_index = 1;
        break;
    case 2: // 2 monsters
        table_index = 2;
        break;
    case 3: // 3-6 monsters
    case 4:
    case 5:
    case 6:
        table_index = 3;
        break;
    case 7: // 7-8 monsters
    case 8:
    case 9:
    case 10:
        table_index = 4;
        break;
    case 11: // 11-14 monsters
    case 12:
    case 13:
    case 14:
        table_index = 5;
        break;
    default: // 15+ monsters
        table_index = 6;
    }

    // If we have few characters, up the modifier.
    if (num_adventurers <= 2)
    {
        table_index++;
    }
    // If we have many characters, lower the modifier.
    else if (num_adventurers >= 6)
    {
        table_index--;
    }

    // Return the modifier that
    return monster_encounter_modifiers.at(table_index);
}

std::map<float, uint32_t> Encounter::get_monster_map(const std::vector<uint32_t>& monsters)
{
    std::map<float, uint32_t> monster_map;
    // Fill out the list so we can get the desired xp.
    for (auto monster_xp : monsters)
    {
        auto monster_cr = get_monster_cr(monster_xp);
        monster_map[monster_cr]++;
    }

    return monster_map;
}

void Encounter::set_minimum_monster_xp()
{
    m_minimum_monster_xp_[easy] = get_minimum_monster_xp(easy);
    m_minimum_monster_xp_[medium] = get_minimum_monster_xp(medium);
    m_minimum_monster_xp_[hard] = get_minimum_monster_xp(hard);
    m_minimum_monster_xp_[deadly] = get_minimum_monster_xp(deadly);
}

uint32_t Encounter::get_minimum_monster_xp(const difficulty& difficulty) const
{
    const auto desired_xp = m_party_.get_desired_xp(difficulty);

    if(m_num_monsters_ == 0)
    {
        return 0;
    }

    const auto lowest_xp = desired_xp / m_num_monsters_;
    auto last_xp = 0;

    for(auto xp : monster_xp_table)
    {
        if (lowest_xp <= xp)
        {
            return last_xp;
        }
        last_xp = xp;
    }

    return 0;
}

void Encounter::fill_out_encounters()
{
    m_valid_battles_.clear();
    std::vector<uint32_t> monsters;
    fill_out_helper(monsters, easy);
    monsters.clear();
    fill_out_helper(monsters, medium);
    monsters.clear();
    fill_out_helper(monsters, hard);
    monsters.clear();
    fill_out_helper(monsters, deadly);
}

void Encounter::fill_out_helper(std::vector<uint32_t>& current_monsters, const difficulty& difficulty)
{
    // Get the monster map.
    const auto monster_map = get_monster_map(current_monsters);
    const auto xp = get_battle_xp(monster_map) * get_xp_modifier(static_cast<uint32_t>(current_monsters.size()));

    // Get the lower and upper bounds on xp.
    const auto low_desired = m_party_.get_lower_desired_xp(difficulty);
    const auto upper_desired = m_party_.get_upper_desired_xp(difficulty);

    // Get the checks that need to be true to add the monsters into the list.
    const auto correct_num_monsters = current_monsters.size() <= m_num_monsters_;
    const auto in_xp_range = xp >= low_desired && xp <= upper_desired;
    const auto correct_unique_monsters = monster_map.size() <= m_num_unique_monsters_;

    // If we have the correct number of monsters and it is in range, success!
    if(correct_num_monsters && in_xp_range && correct_unique_monsters)
    {
        m_valid_battles_[difficulty].insert(monster_map);
    }
    else if (current_monsters.size() < m_num_monsters_)
    {
        // Go through all of the xp tables and get the monsters.
        for(auto new_xp : monster_xp_table)
        {
            // If the current xp + new monster xp is over the upper_desired range, don't even try to add it in.
            // Also, don't try to add in monsters that are lower than the minimum xp threshold.
            if (xp + new_xp < upper_desired && new_xp >= m_minimum_monster_xp_[difficulty])
            {
                current_monsters.push_back(new_xp);
                fill_out_helper(current_monsters, difficulty);
                current_monsters.pop_back();
            }
        }
    }

}
