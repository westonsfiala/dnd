#pragma once
#include <map>
#include "Tables.h"

class Party
{
public:
    Party() = default;
    Party(const Party& other) = default;
    ~Party() = default;

    bool add_adventurer(const uint32_t& level);
    bool remove_adventurer(const uint32_t& level);

    uint32_t get_num_adventurers() const;
    uint32_t get_num_adventurers(const uint32_t& level) const;

    static uint32_t get_adventurer_xp(const uint32_t& level, const difficulty& difficulty);

    uint32_t get_desired_xp(const difficulty& difficulty) const;
    uint32_t get_lower_desired_xp(const difficulty& difficulty) const;
    uint32_t get_upper_desired_xp(const difficulty& difficulty) const;

private:

    static const float upper_xp_modifier;
    static const float lower_xp_modifier;

    void calculate_desired_xp();
    uint32_t get_battle_xp(const difficulty& difficulty) const;

    std::map<uint32_t, uint32_t> m_adventurer_map_;
    std::map<difficulty, uint32_t> m_desired_xp_map_;
    std::map<difficulty, uint32_t> m_desired_lower_xp_map_;
    std::map<difficulty, uint32_t> m_desired_upper_xp_map_;

};
