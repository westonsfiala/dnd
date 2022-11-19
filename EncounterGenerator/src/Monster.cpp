#include "Monster.h"

Monster::Monster() :
    mName{ "" },
    mCr{ Cr::INVALID },
    mCreatureSize{ CreatureSize::INVALID },
    mCreatureType{ CreatureType::INVALID },
    mBook{ "" },
    mPage{0}
{
}

bool Monster::isValid() const
{
    if (mName.empty())
    {
        return false;
    }
    if(mCr == Cr::INVALID)
    {
        return false;
    }
    if(mCreatureSize == CreatureSize::INVALID)
    {
        return false;
    }
    if(mCreatureType == CreatureType::INVALID)
    {
        return false;
    }
    if(mBook.empty())
    {
        return false;
    }
    return true;
}

std::string Monster::getName() const
{
    return mName;
}

void Monster::setName(const std::string& name)
{
    mName = name;
}

Cr Monster::getCr() const
{
    return mCr;
}

void Monster::setCr(const Cr cr)
{
    mCr = cr;
}

CreatureSize Monster::getCreatureSize() const
{
    return mCreatureSize;
}

void Monster::setCreatureSize(const CreatureSize creatureSize)
{
    mCreatureSize = creatureSize;
}

CreatureType Monster::getCreatureType() const
{
    return mCreatureType;
}

void Monster::setCreatureType(const CreatureType creatureType)
{
    mCreatureType = creatureType;
}

std::string Monster::getBookLocation() const
{
    return getBook() + " " + std::to_string(getPage());
}

std::string Monster::getBook() const
{
    return mBook;
}

void Monster::setBook(const std::string& book)
{
    mBook = book;
}

uint32_t Monster::getPage() const
{
    return mPage;
}

void Monster::setPage(const uint32_t page)
{
    mPage = page;
}
