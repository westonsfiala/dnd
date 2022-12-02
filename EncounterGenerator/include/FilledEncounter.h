#pragma once

#include "GeneratorUtilities.h"
#include "Monster.h"

#include <map>

using namespace DnD;

class FilledEncounter
{
public:
    FilledEncounter();
    ~FilledEncounter() = default;

    /**
     * \brief Add monsters to this encounter.
     * \param monster A monster present in this encounter
     * \param numMonsters The number of monsters you want to add.
     */
    void addMonsters(const Monster& monster, uint32_t numMonsters);

    /**
     * \brief Remove monsters from this encounter.
     * \param monster The monster you want to remove.
     * \param numMonsters The number of monsters you want to remove.
     */
    void removeMonsters(const Monster& monster, uint32_t numMonsters);

    /**
     * \brief Get the monster Crs that are in this encounter and how many of them there are.
     * \return Monster CR map of this encounter.
     */
    std::map<Monster, uint32_t> getMonsterMap() const;

    /**
     * \brief Get the number of unique monsters in this encounter.
     * \return Number of unique monsters in this encounter.
     */
    uint32_t getNumUniqueMonsters() const;

    /**
     * \brief Get the total number of monsters in this encounter.
     * \return Number of total monsters in this counter.
     */
    uint32_t getNumTotalMonsters() const;

    /**
     * \brief Gets the xp rewards for this encounter.
     * \return Xp reward for this encounter.
     */
    uint32_t getEncounterXp() const;

    /**
     * \brief Converts the current encounter into a string.
     *
     * Has the form "X name(book page) : Y name(book page) ...".
     * \return String form of an encounter.
     */
    std::string toString() const;

private:
    std::map<Monster, uint32_t> mMonsterMap;

};
