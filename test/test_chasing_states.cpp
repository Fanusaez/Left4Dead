
#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/states/idle.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/zombie_states/chasing_states/chase_walking.h"
#include "game_logic/zombie_states/chasing_states/chase_running.h"

void testWalkerChangeChaseStateToRunning(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Infected walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    walker.change_chase_state_to_running();

    ChaseRunning* walker_chase_state = dynamic_cast<ChaseRunning*>(walker.get_chasing_state());

    TEST_ASSERT(walker_chase_state != nullptr);
}

TEST_LIST = {
        {"Test Walker changes chase state", testWalkerChangeChaseStateToRunning},
        {NULL, NULL}
};