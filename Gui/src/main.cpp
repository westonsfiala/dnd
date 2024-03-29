#include "EncounterGenerator.h"
#include "Party.h"
#include "FileHelper.h"

#include <string>

using namespace DnD;

std::string convertToString(const Difficulty &difficulty, const Encounter &encounter)
{
    auto battleString = "Battle Difficulty: " + GeneratorUtilities::toStringDifficulty(difficulty) + ".\nMonsters = { ";

    battleString += encounter.toString();

    battleString += "}";

    return battleString;
}

int main()
{
    MonsterList monsterList = FileHelper::parseJson("C:/work/GitHub/dnd/Resources/Monster_List_Json.json");

    for(auto numAdventurers = 3; numAdventurers <=6; ++numAdventurers)
    {
        for(auto numUniqueMonsters = 1; numUniqueMonsters <= 2; ++numUniqueMonsters)
        {
            std::string randomEncounterCsvString = "";
            uint32_t count = 1;

            // Create a list of 2000 random encounters formed from a series of Medium => Insanity battles.
            for(auto level = 1; level <= 20; level++)
            {
                Party myParty;
                myParty.addAdventurer(level, numAdventurers);
                const EncounterGenerator myEncounter(myParty, numUniqueMonsters, myParty.getNumAdventurers() * 25);

                auto mediumEncounters = monsterList.fillEncounters(myEncounter.getEncounters(Difficulty::Medium, 30));
                auto hardEncounters = monsterList.fillEncounters(myEncounter.getEncounters(Difficulty::Hard, 30));
                auto deadlyEncounters = monsterList.fillEncounters(myEncounter.getEncounters(Difficulty::Deadly, 30));
                auto insanityEncounters = monsterList.fillEncounters(myEncounter.getEncounters(Difficulty::Insanity, 10));

                auto processEncounters = [&](const std::vector<FilledEncounter>& encounterList, Difficulty difficulty)
                {
                    for (const auto& encounter : encounterList)
                    {
                        randomEncounterCsvString += std::to_string(count) + "," + GeneratorUtilities::toStringDifficulty(difficulty) + "," + encounter.toCsvString() + "\n";
                        count++;
                    }
                };

                processEncounters(mediumEncounters, Difficulty::Medium);
                processEncounters(hardEncounters, Difficulty::Hard);
                processEncounters(deadlyEncounters, Difficulty::Deadly);
                processEncounters(insanityEncounters, Difficulty::Insanity);
            }

            auto outputFileName = "C:/work/GitHub/dnd/Resources/RandomEncounters" + std::to_string(numAdventurers) + "Adventurers" + std::to_string(numUniqueMonsters) + "Monsters.csv";

            FileHelper::writeToFile(outputFileName, randomEncounterCsvString);
        }
    }

    /* Manual flow.
    Party myParty;

    myParty.addAdventurer(5,4);

    const EncounterGenerator myEncounter(myParty, 1, myParty.getNumAdventurers() * 25);

    const auto randomBattlesEasy = myEncounter.getEncounters(Difficulty::Easy,2);
    const auto randomBattlesMedium = myEncounter.getEncounters(Difficulty::Medium, 2);
    const auto randomBattlesHard = myEncounter.getEncounters(Difficulty::Hard, 2);
    const auto randomBattlesDeadly = myEncounter.getEncounters(Difficulty::Deadly, 2);
    const auto randomBattlesInsanity = myEncounter.getEncounters(Difficulty::Insanity, 2);

    const auto easyString1 = convertToString(Difficulty::Easy, randomBattlesEasy[0]);
    const auto easyString2 = convertToString(Difficulty::Easy, randomBattlesEasy[1]);
    const auto mediumString1 = convertToString(Difficulty::Medium, randomBattlesMedium[0]);
    const auto mediumString2 = convertToString(Difficulty::Medium, randomBattlesMedium[1]);
    const auto hardString1 = convertToString(Difficulty::Hard, randomBattlesHard[0]);
    const auto hardString2 = convertToString(Difficulty::Hard, randomBattlesHard[1]);
    const auto deadlyString1 = convertToString(Difficulty::Deadly, randomBattlesDeadly[0]);
    const auto deadlyString2 = convertToString(Difficulty::Deadly, randomBattlesDeadly[1]);
    const auto insanityString1 = convertToString(Difficulty::Insanity, randomBattlesInsanity[0]);
    const auto insanityString2 = convertToString(Difficulty::Insanity, randomBattlesInsanity[1]);

    const auto output = easyString1 + "\n\n" + easyString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        mediumString1 + "\n\n" + mediumString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        hardString1 + "\n\n" + hardString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        deadlyString1 + "\n\n" + deadlyString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        insanityString1 + "\n\n" + insanityString2;

    */
    return 0;
}
