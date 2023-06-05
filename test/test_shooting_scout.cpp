#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/weapon.h"
#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define STARTING_DAMAGE 40
#define DAMAGE_REDUCTION 10

void testSoldierShootsScoutWith2InfectedsInLineDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker1(3,8, map);
    map.add_zombie(&walker1, 3, 8);

    Infected walker2(3,9, map);
    map.add_zombie(&walker2, 3, 9);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_ASSERT(remaining_health1 == (100 - STARTING_DAMAGE));
    TEST_ASSERT(remaining_health2 == (100 - (STARTING_DAMAGE - DAMAGE_REDUCTION)));
}

void testSoldierShootsScoutWith3InfectedsInLineDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker1(4,7, map);
    map.add_zombie(&walker1, 4, 7);

    Infected walker2(4,8, map);
    map.add_zombie(&walker2, 4, 8);

    Infected walker3(4,9, map);
    map.add_zombie(&walker3, 4, 9);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    TEST_ASSERT(remaining_health1 == (100 - STARTING_DAMAGE));
    TEST_ASSERT(remaining_health2 == (100 - (STARTING_DAMAGE - DAMAGE_REDUCTION)));
    TEST_ASSERT(remaining_health3 == (100 - (STARTING_DAMAGE - 2*DAMAGE_REDUCTION)));
}

void testSoldierShootsScoutWith2InfectedsInLineUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Infected walker2(3,0, map);
    map.add_zombie(&walker2, 3, 0);

    Infected walker1(3,1, map);
    map.add_zombie(&walker1, 3, 1);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_ASSERT(remaining_health1 == 100 - STARTING_DAMAGE);
    TEST_ASSERT(remaining_health2 == 100 - (STARTING_DAMAGE - DAMAGE_REDUCTION));
}

void testSoldierShootsScoutWith3InfectedsInLineUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Infected walker3(3,0, map);
    map.add_zombie(&walker3, 3, 0);

    Infected walker2(3,1, map);
    map.add_zombie(&walker2, 3, 1);

    Infected walker1(3,2, map);
    map.add_zombie(&walker1, 3, 2);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    TEST_ASSERT(remaining_health1 == 100 - STARTING_DAMAGE);
    TEST_ASSERT(remaining_health2 == 100 - (STARTING_DAMAGE - DAMAGE_REDUCTION));
    TEST_ASSERT(remaining_health3 == 100 - (STARTING_DAMAGE - 2*DAMAGE_REDUCTION));
}

TEST_LIST = {
        {"Soldier shoots down scout with one walker behind another, damages both", testSoldierShootsScoutWith2InfectedsInLineDown},
        {"Soldier shoots down scout with 3 walker in line, damages all of them", testSoldierShootsScoutWith3InfectedsInLineDown},
        {"Soldier shoots up scout with 2 walker in line, damages all of them",testSoldierShootsScoutWith2InfectedsInLineUp},
        {"Soldier shoots up scout with 3 walker in line, damages all of them",testSoldierShootsScoutWith3InfectedsInLineUp},
        {NULL, NULL},
};