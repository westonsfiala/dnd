#include "stdafx.h"
#include "Encounter.h"
#include "Party.h"

int main()
{
    Party my_party;

    my_party.add_adventurer(7);
    my_party.add_adventurer(7);
    my_party.add_adventurer(8);
    my_party.add_adventurer(8);

    Encounter my_encounter(my_party, 8);

    auto battles_easy = my_encounter.get_all_battles(easy);
    auto battles_medium = my_encounter.get_all_battles(medium);
    auto battles_hard = my_encounter.get_all_battles(hard);
    auto battles_deadly = my_encounter.get_all_battles(deadly);

    return 0;
}

