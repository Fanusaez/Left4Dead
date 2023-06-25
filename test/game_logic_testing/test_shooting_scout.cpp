#include <cstdint>
#include "../acutest.h"
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

void testSoldierShootsScoutWith2InfectedsInLineRight(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker1(8, 3, 0, map, 0, 0);
    map.add_zombie(&walker1, 8, 3);

    Infected walker2(9, 3, 0, map, 0, 0);
    map.add_zombie(&walker2, 9, 3);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 == (100 - STARTING_DAMAGE));
    TEST_CHECK(remaining_health2 == (100 - (STARTING_DAMAGE - DAMAGE_REDUCTION)));
     map.empty_vectors();
}

void testSoldierShootsScoutWith3InfectedsInLineRight(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 4, 0);
    map.add_soldier(&soldier, 3, 4);

    Infected walker1(7, 4, 0, map, 0, 0);
    map.add_zombie(&walker1, 7, 4);

    Infected walker2(8, 4, 0, map, 0, 0);
    map.add_zombie(&walker2, 8, 4);

    Infected walker3(9, 4, 0, map, 0, 0);
    map.add_zombie(&walker3, 9, 4);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    TEST_CHECK(remaining_health1 == (100 - STARTING_DAMAGE));
    TEST_CHECK(remaining_health2 == (100 - (STARTING_DAMAGE - DAMAGE_REDUCTION)));
    TEST_CHECK(remaining_health3 == (100 - (STARTING_DAMAGE - 2*DAMAGE_REDUCTION)));
     map.empty_vectors();
}

void testSoldierShootsScoutWith2InfectedsInLineLeft(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 3, 0);
    map.add_soldier(&soldier, 8, 3);

    Infected walker2(0, 3, 0, map, 0, 0);
    map.add_zombie(&walker2, 0, 3);

    Infected walker1(1, 3, 0, map, 0, 0);
    map.add_zombie(&walker1, 1, 3);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 == 100 - STARTING_DAMAGE);
    TEST_CHECK(remaining_health2 == 100 - (STARTING_DAMAGE - DAMAGE_REDUCTION));
     map.empty_vectors();
}

void testSoldierShootsScoutWith3InfectedsInLineLeft(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 3, 0);
    map.add_soldier(&soldier, 8, 3);

    Infected walker3(0, 3, 0, map, 0, 0);
    map.add_zombie(&walker3, 0, 3);

    Infected walker2(1, 3, 0, map, 0, 0);
    map.add_zombie(&walker2, 1, 3);

    Infected walker1(2, 3, 0, map, 0, 0);
    map.add_zombie(&walker1, 2, 3);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    TEST_CHECK(remaining_health1 == 100 - STARTING_DAMAGE);
    TEST_CHECK(remaining_health2 == 100 - (STARTING_DAMAGE - DAMAGE_REDUCTION));
    TEST_CHECK(remaining_health3 == 100 - (STARTING_DAMAGE - 2*DAMAGE_REDUCTION));
     map.empty_vectors();
}

TEST_LIST = {
        {"Soldier shoots Right scout with one walker behind another, damages both", testSoldierShootsScoutWith2InfectedsInLineRight},
        {"Soldier shoots right scout with 3 walker in line, damages all of them", testSoldierShootsScoutWith3InfectedsInLineRight},
        {"Soldier shoots left scout with 2 walker in line, damages all of them",testSoldierShootsScoutWith2InfectedsInLineLeft},
        {"Soldier shoots left scout with 3 walker in line, damages all of them",testSoldierShootsScoutWith3InfectedsInLineLeft},
        {NULL, NULL},
};