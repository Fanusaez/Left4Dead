#include <cstdint>
#include <iostream>
#include "../acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/idf.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define WALKER_SPEED 1
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1
//************************************** NO DAMAGE ********************************************************//

void testInfectedtriesToAttackSoldierButOutOfRange() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 2, 0);
    map.add_soldier(&soldier, 8, 2);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) {
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
     map.empty_vectors();
}

void testInfectedtriesToAttackSoldierButOutOfRange2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 7 , 4, 0);
    map.add_soldier(&soldier, 7, 4);

    Infected walker(6 , 6, 0, map);
    map.add_zombie(&walker, 6, 6);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
     map.empty_vectors();
}

void testInfectedtriesToAttackSoldierButOutOfRange3() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3 , 4, 0);
    map.add_soldier(&soldier, 3, 4);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
     map.empty_vectors();
}

void testInfectedtriesToAttackSoldierButOutOfRange4() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 7 , 6, 0);
    map.add_soldier(&soldier, 7, 6);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
     map.empty_vectors();
}

void testInfectedtriesToAttackSoldierButOutOfRange5() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3 , 6, 0);
    map.add_soldier(&soldier, 3, 6);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health == 100);
     map.empty_vectors();
}

//****************************************************** DAMAGE ************************************************

void testInfectedDamagesSoldier() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 6, 0);
    map.add_soldier(&soldier, 5, 6);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
     map.empty_vectors();
}

void testInfectedDamagesSoldier2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 4, 0);
    map.add_soldier(&soldier, 5, 4);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
     map.empty_vectors();
}

void testInfectedDamagesSoldier3() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 4 , 4, 0);
    map.add_soldier(&soldier, 4, 4);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
     map.empty_vectors();
}

void testInfectedDamagesSoldier4() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 6 , 4, 0);
    map.add_soldier(&soldier, 6, 4);

    Infected walker(5 , 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
     map.empty_vectors();
}

void testInfectedDamagesSoldier5() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 6, 0);
    map.add_soldier(&soldier, 5, 6);

    Infected walker(6 , 6, 0, map);
    map.add_zombie(&walker, 6, 6);

    for (int i = 0; i < 10; i++) { // enough to encounter the soldier face to face
        map.attack_soldiers(i);
    }

    std::int16_t soldier_health = soldier.get_health();

    TEST_CHECK(soldier_health < 100);
     map.empty_vectors();
}

TEST_LIST = {
        {"Infected tries to attack soldier", testInfectedtriesToAttackSoldierButOutOfRange},
        {"Infected tries to attack soldier 2", testInfectedtriesToAttackSoldierButOutOfRange2},
        {"Infected tries to attack soldier 3", testInfectedtriesToAttackSoldierButOutOfRange3},
        {"Infected tries to attack soldier 4", testInfectedtriesToAttackSoldierButOutOfRange4},
        {"Infected tries to attack soldier 5", testInfectedtriesToAttackSoldierButOutOfRange5},
        {"Infected damages soldier", testInfectedDamagesSoldier},
        {"Infected damages soldier 2", testInfectedDamagesSoldier2},
        {"Infected damages soldier 3", testInfectedDamagesSoldier3},
        {"Infected damages soldier 4", testInfectedDamagesSoldier4},
        {"Infected damages soldier 5", testInfectedDamagesSoldier4},
        {NULL, NULL},

};

