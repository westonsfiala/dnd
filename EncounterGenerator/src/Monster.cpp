#include "Monster.h"

Monster::Monster(const std::string& name, const Cr& cr, const CreatureSize& creatureSize, const CreatureType& creatureType, const std::string& book, const uint32_t& page) :
    mName{ name },
    mCr{ cr },
    mCreatureSize{ creatureSize },
    mCreatureType{ creatureType },
    mBook{ book },
    mPage{ page }
{
}

bool Monster::operator==(const Monster& other) const
{

    if(mName != other.mName)
    {
        return false;
    }
    if (mCr != other.mCr)
    {
        return false;
    }
    if (mCreatureSize != other.mCreatureSize)
    {
        return false;
    }
    if (mCreatureType != other.mCreatureType)
    {
        return false;
    }
    if (mBook != other.mBook)
    {
        return false;
    }
    if (mPage != other.mPage)
    {
        return false;
    }
    return true;
}

bool Monster::operator<(const Monster& other) const
{
    if(mCr != other.mCr)
    {
        return mCr < other.mCr;
    }

    return mName < other.mName;
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

Cr Monster::getCr() const
{
    return mCr;
}

CreatureSize Monster::getCreatureSize() const
{
    return mCreatureSize;
}

CreatureType Monster::getCreatureType() const
{
    return mCreatureType;
}

std::string Monster::getBookLocation() const
{
    return getBook() + " " + std::to_string(getPage());
}

std::string Monster::getBook() const
{
    return mBook;
}

uint32_t Monster::getPage() const
{
    return mPage;
}
