#pragma once
#include "GeneratorUtilities.h"

#include <map>

using namespace DnD;

class Encounter
{
public:
    Encounter();
    ~Encounter() = default;

    /**
     * \brief Add monsters to this encounter.
     * \param cr The Cr of the monsters you want to add.
     * \param numMonsters The number of monsters you want to add.
     */
    void addMonsters(Cr cr, uint32_t numMonsters);

    /**
     * \brief Remove monsters from this encounter.
     * \param cr The Cr of the monsters you want to remove.
     * \param numMonsters The number of monsters you want to remove.
     */
    void removeMonsters(Cr cr, uint32_t numMonsters);

    /**
     * \brief Get the monsters that are in this encounter.
     * \return Monster map of this encounter.
     */
    std::map<Cr, uint32_t> getMonsters() const;

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
     * Has the form "X Cr Y : A Cr B ...".
     * \return String form 
     */
    std::string toString() const;

private:
    std::map<Cr, uint32_t> mMonsterMap;
};
