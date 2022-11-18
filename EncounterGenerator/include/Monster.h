#pragma once
#include <string>

class Monster
{
public:
    Monster() = default;
    Monster(const Monster& other) = default;
    ~Monster() = default;


private:
    std::string mName;


};
