#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/idf.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define WALKER_SPEED 0.3

//************************************** NO DAMAGE ********************************************************//

void testWalkertriesToAttackSoldierButOutOfRange() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
}

void testWalkertriesToAttackSoldierButOutOfRange2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 7, 4);
    map.add_soldier(&soldier, 7, 4);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
}

void testWalkertriesToAttackSoldierButOutOfRange3() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 4);
    map.add_soldier(&soldier, 3, 4);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
}

void testWalkertriesToAttackSoldierButOutOfRange4() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 7, 6);
    map.add_soldier(&soldier, 7, 6);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
}

void testWalkertriesToAttackSoldierButOutOfRange5() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 6);
    map.add_soldier(&soldier, 3, 6);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
}

//****************************************************** DAMAGE ************************************************

void testWalkerDamagesSoldier() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 6);
    map.add_soldier(&soldier, 5, 6);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
}

void testWalkerDamagesSoldier2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 4);
    map.add_soldier(&soldier, 5, 4);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
}

void testWalkerDamagesSoldier3() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 4, 4);
    map.add_soldier(&soldier, 4, 4);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
}

void testWalkerDamagesSoldier4() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 6, 4);
    map.add_soldier(&soldier, 6, 4);

    Walker walker(5,5, WALKER_SPEED);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
}

TEST_LIST = {
        {"Walker tries to attack soldier", testWalkertriesToAttackSoldierButOutOfRange},
        {"Walker tries to attack soldier 2", testWalkertriesToAttackSoldierButOutOfRange2},
        {"Walker tries to attack soldier 3", testWalkertriesToAttackSoldierButOutOfRange3},
        {"Walker tries to attack soldier 4", testWalkertriesToAttackSoldierButOutOfRange4},
        {"Walker tries to attack soldier 5", testWalkertriesToAttackSoldierButOutOfRange5},
        {"Walker damages soldier", testWalkerDamagesSoldier},
        {"Walker damages soldier 2", testWalkerDamagesSoldier2},
        {"Walker damages soldier 3", testWalkerDamagesSoldier3},
        {"Walker damages soldier 4", testWalkerDamagesSoldier4},
        {NULL, NULL},

};

