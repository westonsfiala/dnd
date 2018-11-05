#include "Encounter.h"
#include "Party.h"

int main()
{
    Party my_party;

    my_party.add_adventurer(3);
    my_party.add_adventurer(3);
    my_party.add_adventurer(3);
    my_party.add_adventurer(3);
    my_party.add_adventurer(3);

    Encounter my_encounter(my_party, my_party.get_num_adventurers() * 2);

    auto battles_easy = my_encounter.get_all_battles(easy);
    auto battles_medium = my_encounter.get_all_battles(medium);
    auto battles_hard = my_encounter.get_all_battles(hard);
    auto battles_deadly = my_encounter.get_all_battles(deadly);

    auto random_battle_easy = my_encounter.get_battle(easy);
    auto random_battle_medium = my_encounter.get_battle(medium);
    auto random_battle_hard = my_encounter.get_battle(hard);
    auto random_battle_deadly = my_encounter.get_battle(deadly);

    return 0;
}

