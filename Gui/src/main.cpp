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

    Party myParty;

    myParty.addAdventurer(12,6);

    const EncounterGenerator myEncounter(myParty, 1, myParty.getNumAdventurers() * 4);

    const auto battlesEasy = myEncounter.getAllEncounters(Difficulty::Easy);
    const auto battlesMedium = myEncounter.getAllEncounters(Difficulty::Medium);
    const auto battlesHard = myEncounter.getAllEncounters(Difficulty::Hard);
    const auto battlesDeadly = myEncounter.getAllEncounters(Difficulty::Deadly);
    const auto battlesInsanity = myEncounter.getAllEncounters(Difficulty::Insanity);

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

    const auto filledEncounters = monsterList.fillEncounters(battlesHard);

    const auto output = easyString1 + "\n\n" + easyString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        mediumString1 + "\n\n" + mediumString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        hardString1 + "\n\n" + hardString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        deadlyString1 + "\n\n" + deadlyString2 + "\n\n" +
                        "-------------------------------------------\n" +
                        insanityString1 + "\n\n" + insanityString2;

    return 0;
}
