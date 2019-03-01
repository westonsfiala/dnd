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

    myParty.addAdventurer(9);
    myParty.addAdventurer(9);
    myParty.addAdventurer(9);
    myParty.addAdventurer(9);

    const Encounter myEncounter(myParty, myParty.getNumAdventurers() * 5);

    const auto battlesEasy = myEncounter.getAllBattles(Difficulty::Easy);
    const auto battlesMedium = myEncounter.getAllBattles(Difficulty::Medium);
    const auto battlesHard = myEncounter.getAllBattles(Difficulty::Hard);
    const auto battlesDeadly = myEncounter.getAllBattles(Difficulty::Deadly);
    const auto battlesInsanity = myEncounter.getAllBattles(Difficulty::Insanity);

    const auto randomBattleEasy = myEncounter.getBattle(Difficulty::Easy);
    const auto randomBattleMedium = myEncounter.getBattle(Difficulty::Medium);
    const auto randomBattleHard = myEncounter.getBattle(Difficulty::Hard);
    const auto randomBattleDeadly = myEncounter.getBattle(Difficulty::Deadly);
    const auto randomBattleInsanity = myEncounter.getBattle(Difficulty::Insanity);

    const auto easyString = toString(Difficulty::Easy, randomBattleEasy);
    const auto mediumString = toString(Difficulty::Medium, randomBattleMedium);
    const auto hardString = toString(Difficulty::Hard, randomBattleHard);
    const auto deadlyString = toString(Difficulty::Deadly, randomBattleDeadly);
    const auto insanityString = toString(Difficulty::Insanity, randomBattleInsanity);

    return 0;
}
