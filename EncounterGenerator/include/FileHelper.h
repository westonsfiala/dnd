#pragma once
#include "MonsterList.h"

using namespace DnD;

class FileHelper
{
public:
    /**
     * \brief Parses the given json file into a monster list. 
     * \param jsonPath Path to the json file containing monster info.
     * \return MonsterList formed from the info in the json file.
     */
    static MonsterList parseJson(const std::string& jsonPath);

    /**
     * \brief Writes the given string to the given filepath.
     * \param filePath Path of the file that is to be written.
     * \param fileContent Contents that will be written to the file.
     */
    static void writeToFile(const std::string& filePath, const std::string& fileContent);
};

