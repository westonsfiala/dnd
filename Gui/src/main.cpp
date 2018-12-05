#include "Encounter.h"
#include "Party.h"
#include <string>

std::string toString(const Difficulty &difficulty, const std::map<Cr, uint32_t> &battleMap)
{
    auto battleString = "Battle Difficulty: " + GenUtil::toString(difficulty) + ".\nMonsters = { ";

    for(auto monsterPair : battleMap)
    {
        battleString += std::to_string(monsterPair.second) + " CR " + GenUtil::toString(monsterPair.first) + " : " ;
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

    myParty.addAdventurer(8);
    myParty.addAdventurer(8);

    const Encounter myEncounter(myParty, myParty.getNumAdventurers() * 8);

    const auto battlesEasy = myEncounter.getAllBattles(Easy);
    const auto battlesMedium = myEncounter.getAllBattles(Medium);
    const auto battlesHard = myEncounter.getAllBattles(Hard);
    const auto battlesDeadly = myEncounter.getAllBattles(Deadly);

    const auto randomBattleEasy = myEncounter.getBattle(Easy);
    const auto randomBattleMedium = myEncounter.getBattle(Medium);
    const auto randomBattleHard = myEncounter.getBattle(Hard);
    const auto randomBattleDeadly = myEncounter.getBattle(Deadly);

    const auto easyString = toString(Easy, randomBattleEasy);
    const auto mediumString = toString(Medium, randomBattleMedium);
    const auto hardString = toString(Hard, randomBattleHard);
    const auto deadlyString = toString(Deadly, randomBattleDeadly);

    return 0;
}
