#include <cstdint>
#include "../acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define CLOSE_RANGE_DAMAGE 30
#define LONG_RANGE_DAMAGE 15

void testSoldierShootsIdfCloseRangeLeft(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(2, 3, 0,  map, 0, 0);
    map.add_zombie(&walker, 2, 3);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfCloseRangeRight(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(7, 3, 0, map, 0, 0);
    map.add_zombie(&walker, 7, 3);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfCloseRangeLeftNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    soldier.move_up();

    Infected walker(2, 2, 0, map, 0, 0);
    map.add_zombie(&walker, 2, 2);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfCloseRangeRightNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 4, 0);
    map.add_soldier(&soldier, 3, 4);

    soldier.move_down();

    Infected walker(7, 4, 0, map, 0, 0);
    map.add_zombie(&walker, 7, 4);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - CLOSE_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfLongRangeLeft(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 5, 3, 0);
    map.add_soldier(&soldier, 5, 3);

    Infected walker(0, 3, 0, map, 0, 0);
    map.add_zombie(&walker, 0, 3);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - LONG_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfLongRangeRight(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(8, 3, 0, map, 0, 0);
    map.add_zombie(&walker, 8, 3);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - LONG_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfLongRangeLeftNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 6, 3, 0);
    map.add_soldier(&soldier, 6, 3);

    soldier.move_up();

    Infected walker(1, 2, 0, map, 0, 0);
    map.add_zombie(&walker, 1, 2);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - LONG_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfLongRangeRightNotSameLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 5, 0);
    map.add_soldier(&soldier, 3, 5);

    soldier.move_up();

    Infected walker(8, 4, 0, map, 0, 0);
    map.add_zombie(&walker, 8, 4);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health == 100 - LONG_RANGE_DAMAGE);
     map.empty_vectors();
}

void testSoldierShootsIdfWith2InfectedsInLine(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, 3, 3, 0);
    map.add_soldier(&soldier, 3, 3);

    Infected walker1(8, 3, 0, map, 0, 0);
    map.add_zombie(&walker1, 8, 3);

    Infected walker2(8, 4, 0, map, 0, 0);
    map.add_zombie(&walker2, 8, 4);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 == 100 - LONG_RANGE_DAMAGE);
    TEST_CHECK(remaining_health2 == 100);
     map.empty_vectors();
}



TEST_LIST = {
        {"Soldier shoots Idf close range left", testSoldierShootsIdfCloseRangeLeft},
        {"Soldier shoots Idf close range right",testSoldierShootsIdfCloseRangeRight},
        {"Soldier shoots Idf close range left not same line", testSoldierShootsIdfCloseRangeLeftNotSameLine},
        {"Soldier shoots Idf close range right not same line",testSoldierShootsIdfCloseRangeRightNotSameLine},
        {"Soldier shoots Idf long range left", testSoldierShootsIdfLongRangeLeft},
        {"Soldier shoots Idf long range right",testSoldierShootsIdfLongRangeRight},
        {"Soldier shoots Idf long range left not same line", testSoldierShootsIdfLongRangeLeftNotSameLine},
        {"Soldier shoots Idf long range right not same line",testSoldierShootsIdfLongRangeRightNotSameLine},
        {"Soldier shoots idf with one walker behind another, only damages the first", testSoldierShootsIdfWith2InfectedsInLine},
        {NULL, NULL}
};
