#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define CLOSE_RANGE_DAMAGE 30
#define LONG_RANGE_DAMAGE 15

void testSoldierShootsInfectedDiesAndIsRemovedFromMap(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Scout(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    soldier.set_direction(LEFT);

    for (int i = 0; i < 20; i++) {
        soldier.shoot(i);
    }

    std::int16_t remaining_health = walker.get_health();
    bool free_pos = map.check_free_position(3, 2);

    TEST_CHECK(remaining_health <= 0);
    TEST_CHECK(free_pos == true);
}

TEST_LIST = {
        {"Soldier kills Infected and this disappear from map", testSoldierShootsInfectedDiesAndIsRemovedFromMap},
        {NULL, NULL}
};

