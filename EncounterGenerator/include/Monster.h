#pragma once
#include <string>

#include "GeneratorUtilities.h"

using namespace DnD;

class Monster
{
public:
    Monster();
    Monster(const Monster& other) = default;
    ~Monster() = default;

    bool operator==(const Monster& other) const;
    bool operator<(const Monster& other) const;

    bool isValid() const;

    std::string getName() const;
    void setName(const std::string& name);

    Cr getCr() const;
    void setCr(Cr cr);

    CreatureSize getCreatureSize() const;
    void setCreatureSize(CreatureSize creatureSize);

    CreatureType getCreatureType() const;
    void setCreatureType(CreatureType creatureType);

    std::string getBookLocation() const;

    std::string getBook() const;
    void setBook(const std::string& book);

    uint32_t getPage() const;
    void setPage(uint32_t page);

private:
    std::string mName;
    Cr mCr;
    CreatureSize mCreatureSize;
    CreatureType mCreatureType;
    std::string mBook;
    uint32_t mPage;
};
