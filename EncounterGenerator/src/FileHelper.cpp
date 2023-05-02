#include "FileHelper.h"

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "Monster.h"

using namespace DnD;
using namespace nlohmann;

MonsterList FileHelper::parseJson(const std::string& jsonFilePath)
{
    auto monsterList = MonsterList();

    std::ifstream ifs(jsonFilePath);
    json parsedJson = json::parse(ifs);

    for(const auto& monsterObject : parsedJson)
    {
        auto parsedCr = monsterObject["CR"].get<double>();
        auto parsedName = monsterObject["Name"].get<std::string>();
        auto parsedSize = monsterObject["Size"].get<std::string>();
        auto parsedType = monsterObject["Type"].get<std::string>();
        auto parsedBook = monsterObject["Book"].get<std::string>();
        auto parsedPage = monsterObject["Page"].get<uint32_t>();

        Monster newMonster(
            parsedName, 
            GeneratorUtilities::fromDoubleCr(parsedCr), 
            GeneratorUtilities::fromStringCreatureSize(parsedSize), 
            GeneratorUtilities::fromStringCreatureType(parsedType), 
            parsedBook, 
            parsedPage);

        monsterList.addMonster(newMonster);
    }

    return monsterList;
}

void FileHelper::writeToFile(const std::string& filePath, const std::string& fileContent)
{
    std::ofstream out(filePath);
    out << fileContent;
    out.close();
}
