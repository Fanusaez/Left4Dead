#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/walker.h"
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

void testSoldierShootsScoutWith2WalkersInLineDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker1(3,8, map);
    map.add_zombie(&walker1, 3, 8);

    Walker walker2(3,9, map);
    map.add_zombie(&walker2, 3, 9);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_ASSERT(remaining_health1 == (100 - STARTING_DAMAGE));
    TEST_ASSERT(remaining_health2 == (100 - (STARTING_DAMAGE - DAMAGE_REDUCTION)));
}

void testSoldierShootsScoutWith3WalkersInLineDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker1(4,7, map);
    map.add_zombie(&walker1, 4, 7);

    Walker walker2(4,8, map);
    map.add_zombie(&walker2, 4, 8);

    Walker walker3(4,9, map);
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

void testSoldierShootsScoutWith2WalkersInLineUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker2(3,0, map);
    map.add_zombie(&walker2, 3, 0);

    Walker walker1(3,1, map);
    map.add_zombie(&walker1, 3, 1);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_ASSERT(remaining_health1 == 100 - STARTING_DAMAGE);
    TEST_ASSERT(remaining_health2 == 100 - (STARTING_DAMAGE - DAMAGE_REDUCTION));
}

void testSoldierShootsScoutWith3WalkersInLineUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Walker walker3(3,0, map);
    map.add_zombie(&walker3, 3, 0);

    Walker walker2(3,1, map);
    map.add_zombie(&walker2, 3, 1);

    Walker walker1(3,2, map);
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
        {"Soldier shoots down scout with one walker behind another, damages both", testSoldierShootsScoutWith2WalkersInLineDown},
        {"Soldier shoots down scout with 3 walker in line, damages all of them", testSoldierShootsScoutWith3WalkersInLineDown},
        {"Soldier shoots up scout with 2 walker in line, damages all of them",testSoldierShootsScoutWith2WalkersInLineUp},
        {"Soldier shoots up scout with 3 walker in line, damages all of them",testSoldierShootsScoutWith3WalkersInLineUp},
        {NULL, NULL},
};