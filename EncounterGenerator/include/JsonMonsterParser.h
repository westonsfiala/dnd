#pragma once
#include "MonsterList.h"

using namespace DnD;

class JsonMonsterParser
{
public:
    static MonsterList parseJson(const std::string& jsonPath);
};

