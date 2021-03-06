#include "Encounter.h"
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

    myParty.addAdventurer(6,6);

    const Encounter myEncounter(myParty, 1, myParty.getNumAdventurers() * 5);

    const auto battlesEasy = myEncounter.getAllBattles(Difficulty::Easy);
    const auto battlesMedium = myEncounter.getAllBattles(Difficulty::Medium);
    const auto battlesHard = myEncounter.getAllBattles(Difficulty::Hard);
    const auto battlesDeadly = myEncounter.getAllBattles(Difficulty::Deadly);
    const auto battlesInsanity = myEncounter.getAllBattles(Difficulty::Insanity);

    const auto randomBattleEasy1 = myEncounter.getBattle(Difficulty::Easy);
    const auto randomBattleMedium1 = myEncounter.getBattle(Difficulty::Medium);
    const auto randomBattleMedium2 = myEncounter.getBattle(Difficulty::Medium);
    const auto randomBattleHard1 = myEncounter.getBattle(Difficulty::Hard);
    const auto randomBattleHard2 = myEncounter.getBattle(Difficulty::Hard);
    const auto randomBattleDeadly1 = myEncounter.getBattle(Difficulty::Deadly);
    const auto randomBattleInsanity1 = myEncounter.getBattle(Difficulty::Insanity);

    const auto easyString1 = toString(Difficulty::Easy, randomBattleEasy1);
    const auto mediumString1 = toString(Difficulty::Medium, randomBattleMedium1);
    const auto mediumString2 = toString(Difficulty::Medium, randomBattleMedium2);
    const auto hardString1 = toString(Difficulty::Hard, randomBattleHard1);
    const auto hardString2 = toString(Difficulty::Hard, randomBattleHard2);
    const auto deadlyString1 = toString(Difficulty::Deadly, randomBattleDeadly1);
    const auto insanityString1 = toString(Difficulty::Insanity, randomBattleInsanity1);

    const auto output = easyString1 + "\n\n" + mediumString1 + "\n\n" + mediumString2 + "\n\n" + hardString1 + "\n\n" + hardString2 + "\n\n" + deadlyString1 + "\n\n" + insanityString1;

    return 0;
}
