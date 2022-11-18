#pragma once

#include "GeneratorUtilities.h"


#include <string>
#

class Monster
{
public:
    Monster() = default;
    Monster(const Monster& other) = default;
    ~Monster() = default;

private:
    GeneratorUtilities::Cr mCr;
    std::string mName;
    


};
