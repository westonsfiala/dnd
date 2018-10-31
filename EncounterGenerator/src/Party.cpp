#include "Party.h"
#include "Tables.h"
#include "Encounter.h"


const float Party::upper_xp_modifier = 1.25f;
const float Party::lower_xp_modifier = 0.75f;

bool Party::add_adventurer(const uint32_t& level)
{
    // Only add an adventurer when the level is valid.
    if(level >= 1 && level <= 20)
    {
        const auto current_adventurers = m_adventurer_map_[level];
        m_adventurer_map_[level] = current_adventurers + 1;
        calculate_desired_xp();
        return true;
    }
    return false;
}

bool Party::remove_adventurer(const uint32_t& level)
{
    // Only remove an adventurer when the level is valid.
    if (level >= 1 && level <= 20)
    {
        const auto current_adventurers = m_adventurer_map_[level];
        // If we don't have an adventurer 
        if (current_adventurers != 0)
        {
            m_adventurer_map_[level] = current_adventurers - 1;
            calculate_desired_xp();
            return true;
        }
    }
    return false;
}

uint32_t Party::get_num_adventurers() const
{
    auto num_adventurers = 0;

    for(const auto &adventurers : m_adventurer_map_)
    {
        num_adventurers += adventurers.second;
    }

    return num_adventurers;
}

uint32_t Party::get_num_adventurers(const uint32_t& level) const
{
    if(m_adventurer_map_.count(level) != 0)
    {
        return m_adventurer_map_.at(level);
    }

    return 0;
}

uint32_t Party::get_adventurer_xp(const uint32_t& level, const difficulty& difficulty)
{
    // If the level is invalid, return 0
    if(level < 1 || level > 20)
    {
        return 0;
    }

    switch(difficulty)
    {
    case easy: return easy_battle_adventurer_xp[level-1];
    case medium: return medium_battle_adventurer_xp[level-1];
    case hard: return hard_battle_adventurer_xp[level-1];
    case deadly: return deadly_battle_adventurer_xp[level-1];
    default: return 0;
    }
}

uint32_t Party::get_desired_xp(const difficulty& difficulty) const
{
    switch (difficulty)
    {
    case easy: return m_desired_xp_map_.at(easy);
    case medium: return m_desired_xp_map_.at(medium);
    case hard: return m_desired_xp_map_.at(hard);
    case deadly: return m_desired_xp_map_.at(deadly);
    default: return 0;
    }
}

uint32_t Party::get_lower_desired_xp(const difficulty& difficulty) const
{
    switch (difficulty)
    {
    case easy: return m_desired_lower_xp_map_.at(easy);
    case medium: return m_desired_lower_xp_map_.at(medium);
    case hard: return m_desired_lower_xp_map_.at(hard);
    case deadly: return m_desired_lower_xp_map_.at(deadly);
    default: return 0;
    }
}

uint32_t Party::get_upper_desired_xp(const difficulty& difficulty) const
{
    switch (difficulty)
    {
    case easy: return m_desired_upper_xp_map_.at(easy);
    case medium: return m_desired_upper_xp_map_.at(medium);
    case hard: return m_desired_upper_xp_map_.at(hard);
    case deadly: return m_desired_upper_xp_map_.at(deadly);
    default: return 0;
    }
}

void Party::calculate_desired_xp()
{
    m_desired_xp_map_[easy] = get_battle_xp(easy);
    m_desired_xp_map_[medium] = get_battle_xp(medium);
    m_desired_xp_map_[hard] = get_battle_xp(hard);
    m_desired_xp_map_[deadly] = get_battle_xp(deadly);

    m_desired_lower_xp_map_[easy] = static_cast<uint32_t>(m_desired_xp_map_[easy] * lower_xp_modifier);
    m_desired_lower_xp_map_[medium] = static_cast<uint32_t>(m_desired_xp_map_[medium] * lower_xp_modifier);
    m_desired_lower_xp_map_[hard] = static_cast<uint32_t>(m_desired_xp_map_[hard] * lower_xp_modifier);
    m_desired_lower_xp_map_[deadly] = static_cast<uint32_t>(m_desired_xp_map_[deadly] * lower_xp_modifier);

    m_desired_upper_xp_map_[easy] = static_cast<uint32_t>(m_desired_xp_map_[easy] * upper_xp_modifier);
    m_desired_upper_xp_map_[medium] = static_cast<uint32_t>(m_desired_xp_map_[medium] * upper_xp_modifier);
    m_desired_upper_xp_map_[hard] = static_cast<uint32_t>(m_desired_xp_map_[hard] * upper_xp_modifier);
    m_desired_upper_xp_map_[deadly] = static_cast<uint32_t>(m_desired_xp_map_[deadly] * upper_xp_modifier);
}

uint32_t Party::get_battle_xp(const difficulty& difficulty) const
{
    if(difficulty < easy || difficulty > deadly)
    {
        return 0;
    }

    auto desired_xp = 0;

    for (const auto &adventurers : m_adventurer_map_)
    {
        desired_xp += get_adventurer_xp(adventurers.first, difficulty) * adventurers.second;
    }

    return desired_xp;
}
