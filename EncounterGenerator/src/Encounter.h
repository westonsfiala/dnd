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
    Encounter(const Party& adventurers, const uint32_t& num_monsters);
    ~Encounter() = default;

    std::map<cr, uint32_t> get_battle(const difficulty& difficulty) const;

    std::set<std::map<cr, uint32_t>> get_all_battles(const difficulty& difficulty) const;

    static uint32_t get_battle_xp(const std::map<cr, uint32_t>& monster_map);

private:
    static const std::vector<float> monster_encounter_modifiers;

    float get_xp_modifier(const uint32_t& num_monsters) const;
    static std::map<cr, uint32_t> get_monster_map(const std::vector<uint32_t>& monsters);

    void set_minimum_monster_xp();
    uint32_t get_minimum_monster_xp(const difficulty& difficulty) const;

    void fill_out_encounters();
    void fill_out_helper(std::vector<uint32_t>& current_monsters, const difficulty& difficulty);

    Party m_party_;
    uint32_t m_num_monsters_{};
    uint32_t m_num_unique_monsters_{};
    std::map<difficulty, uint32_t> m_minimum_monster_xp_{};
    std::unordered_map<difficulty, std::set<std::map<cr, uint32_t>>> m_valid_battles_{};
};
