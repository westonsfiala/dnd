#pragma once
#include <string>

#include "GeneratorUtilities.h"

using namespace DnD;

/**
 * \brief A Monster is a creature used in encounters. It stores useful information about the creature and where to find more info.
 */
class Monster
{
public:
    Monster(const std::string& name, const Cr& cr, const CreatureSize& creatureSize, const CreatureType& creatureType, const std::string& book, const uint32_t& page);
    Monster(const Monster& other) = default;
    ~Monster() = default;

    bool operator==(const Monster& other) const;
    bool operator<(const Monster& other) const;

    /**
     * \brief Checks to see if the monster has all of the information needed to be used.
     * \return If any of the field for this monster are not filled out will return false.
     */
    bool isValid() const;

    /**
     * \brief Gets the name of the monster.
     * \return Name of the monster.
     */
    std::string getName() const;

    /**
     * \brief Gets the Cr of the monster.
     * \return Cr of the monster.
     */
    Cr getCr() const;

    /**
     * \brief Gets the creature size of the monster.
     * \return Creature size of the monster.
     */
    CreatureSize getCreatureSize() const;

    /**
     * \brief Gets the creature type of the monster.
     * \return Creature type of the monster
     */
    CreatureType getCreatureType() const;

    /**
     * \brief Gets the book location of the monster.
     * \return Book location of the monster in the form "{Book} {Page}".
     */
    std::string getBookLocation() const;

    /**
     * \brief Gets the book that the monster is described in.
     * \return Book that the monster is described in.
     */
    std::string getBook() const;

    /**
     * \brief Gets the page in the book that the monster is described.
     * \return Page in the book that the monster is described.
     */
    uint32_t getPage() const;

private:
    std::string mName;
    Cr mCr;
    CreatureSize mCreatureSize;
    CreatureType mCreatureType;
    std::string mBook;
    uint32_t mPage;
};
