#include <cstdint>
#include "acutest.h"
#include "../src/soldier.h"
#include "../src/walker.h"
#include "../src/map.h"
#include "../src/game_object.h"
#include "../src/idf.h"
#include "../src/weapon.h"
#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define CLOSE_RANGE_DAMAGE 30
#define LONG_RANGE_DAMAGE 15

void testSoldierShootsIdfCloseRangeUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(3,2);
    map.add_zombie(&walker, 3, 2);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
}

void testSoldierShootsIdfCloseRangeDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(3,7);
    map.add_zombie(&walker, 3, 7);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
}

void testSoldierShootsIdfCloseRangeUpNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(2,2);
    map.add_zombie(&walker, 2, 2);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
}

void testSoldierShootsIdfCloseRangeDownNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(4,7);
    map.add_zombie(&walker, 4, 7);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
}

void testSoldierShootsIdfLongRangeUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 5);
    map.add_soldier(&soldier, 3, 5);

    Walker walker(3,0);
    map.add_zombie(&walker, 3, 0);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - LONG_RANGE_DAMAGE);
}

void testSoldierShootsIdfLongRangeDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - LONG_RANGE_DAMAGE);
}

void testSoldierShootsIdfLongRangeUpNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 6);
    map.add_soldier(&soldier, 3, 6);

    Walker walker(2,1);
    map.add_zombie(&walker, 2, 1);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - LONG_RANGE_DAMAGE);
}

void testSoldierShootsIdfLongRangeDownNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(4,8);
    map.add_zombie(&walker, 4, 8);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100 - LONG_RANGE_DAMAGE);
}

void testSoldierShootsIdfWith2WalkersInLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker1(4,8);
    map.add_zombie(&walker1, 4, 8);

    Walker walker2(4,9);
    map.add_zombie(&walker2, 4, 9);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_ASSERT(remaining_health1 == 100 - LONG_RANGE_DAMAGE);
    TEST_ASSERT(remaining_health2 == 100);
}



TEST_LIST = {
        {"Soldier shoots Idf close range up", testSoldierShootsIdfCloseRangeUp},
        {"Soldier shoots Idf close range down",testSoldierShootsIdfCloseRangeDown},
        {"Soldier shoots Idf close range up not same line", testSoldierShootsIdfCloseRangeUp},
        {"Soldier shoots Idf close range down not same line",testSoldierShootsIdfCloseRangeDown},
        {"Soldier shoots Idf long range up", testSoldierShootsIdfLongRangeUp},
        {"Soldier shoots Idf long range down",testSoldierShootsIdfLongRangeDown},
        {"Soldier shoots Idf long range up not same line", testSoldierShootsIdfLongRangeUp},
        {"Soldier shoots Idf long range down not same line",testSoldierShootsIdfLongRangeDown},
        {"Soldier shoots idf with one walker behind another, only damages the first", testSoldierShootsIdfWith2WalkersInLine},
        {NULL, NULL}
};
