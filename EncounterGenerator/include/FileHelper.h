#pragma once
#include "MonsterList.h"

using namespace DnD;

class FileHelper
{
public:
    static MonsterList parseJson(const std::string& jsonPath);
};

