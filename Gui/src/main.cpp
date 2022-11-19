#include "EncounterGenerator.h"
#include "Party.h"
#include <string>

std::string toString(const Difficulty &difficulty, const std::map<Cr, uint32_t> &battleMap)
{
    auto battleString = "Battle Difficulty: " + toString(difficulty) + ".\nMonsters = { ";

    for(auto monsterPair : battleMap)
    {
        battleString += std::to_string(monsterPair.second) + " CR " + toString(monsterPair.first) + " : " ;
    }
    // Get rid of the fence post stuff.
    battleString.pop_back();
    battleString.pop_back();

    battleString += "}";

    return battleString;
}

int main()
{
    Party myParty;

    myParty.addAdventurer(12,6);

    const EncounterGenerator myEncounter(myParty, 1, myParty.getNumAdventurers() * 25);

    const auto battlesEasy = myEncounter.getAllBattles(Difficulty::Easy);
    const auto battlesMedium = myEncounter.getAllBattles(Difficulty::Medium);
    const auto battlesHard = myEncounter.getAllBattles(Difficulty::Hard);
    const auto battlesDeadly = myEncounter.getAllBattles(Difficulty::Deadly);
    const auto battlesInsanity = myEncounter.getAllBattles(Difficulty::Insanity);

    const auto randomBattlesEasy = myEncounter.getBattles(Difficulty::Easy,2);
    const auto randomBattlesMedium = myEncounter.getBattles(Difficulty::Medium, 2);
    const auto randomBattlesHard = myEncounter.getBattles(Difficulty::Hard, 2);
    const auto randomBattlesDeadly = myEncounter.getBattles(Difficulty::Deadly, 2);
    const auto randomBattlesInsanity = myEncounter.getBattles(Difficulty::Insanity, 2);

    const auto easyString1 = toString(Difficulty::Easy, randomBattlesEasy[0]);
    const auto easyString2 = toString(Difficulty::Easy, randomBattlesEasy[1]);
    const auto mediumString1 = toString(Difficulty::Medium, randomBattlesMedium[0]);
    const auto mediumString2 = toString(Difficulty::Medium, randomBattlesMedium[1]);
    const auto hardString1 = toString(Difficulty::Hard, randomBattlesHard[0]);
    const auto hardString2 = toString(Difficulty::Hard, randomBattlesHard[1]);
    const auto deadlyString1 = toString(Difficulty::Deadly, randomBattlesDeadly[0]);
    const auto deadlyString2 = toString(Difficulty::Deadly, randomBattlesDeadly[1]);
    const auto insanityString1 = toString(Difficulty::Insanity, randomBattlesInsanity[0]);
    const auto insanityString2 = toString(Difficulty::Insanity, randomBattlesInsanity[1]);

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
