#include <cstdint>
#include <iostream>
#include "acutest.h"
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
// ***************************************** Movimiento diagonal *******************************************8

void testMapChaseInfectedDiagonallyUpAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Infected walker(5,5,  map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 3; i++) {
        map.chase_soldiers(i);
    }

    GameObject* walker1 = map.get_object(6, 4);
    GameObject* walker2 = map.get_object(7, 4);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseInfectedDiagonallyUpAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    Infected walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);

    GameObject* walker1 = map.get_object(4, 4);
    GameObject* walker2 = map.get_object(5, 4);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseInfectedDiagonallyDownAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 8);
    map.add_soldier(&soldier, 8, 8);

    Infected walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);

    GameObject* walker1 = map.get_object(6, 6);
    GameObject* walker2 = map.get_object(7, 6);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseInfectedDiagonallyDownAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Infected walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);

    GameObject* walker1 = map.get_object(4, 6);
    GameObject* walker2 = map.get_object(5, 6);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

//*********************************** Up and Down **************************************//

void testMapChaseInfectedUp() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5,8,  map);
    map.add_zombie(&walker, 5, 8);

    for (int i = 0; i < 1; i++) {
        map.chase_soldiers(i);
    }
    GameObject* walker1 = map.get_object(5, 7);
    GameObject* old_pos1= map.get_object(5, 8);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMapChaseInfectedDown() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5,1,  map);
    map.add_zombie(&walker, 5, 1);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    GameObject* walker1 = map.get_object(5, 2);
    GameObject* old_pos1= map.get_object(5, 1);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

//********************************** Right and Left **********************************************//

void testMapChaseInfectedRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Infected walker(2,5,  map);
    map.add_zombie(&walker, 2, 5);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    GameObject* walker1 = map.get_object(3, 5);
    GameObject* old_pos1= map.get_object(2, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMapChaseInfectedLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Infected walker(8,5, map);
    map.add_zombie(&walker, 8, 5);

    map.chase_soldiers(1);

    GameObject* walker1 = map.get_object(7, 5);

    GameObject* old_pos1= map.get_object(9, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

TEST_LIST = {
      //  {"Infected chase soldier diagonally up and right", testMapChaseInfectedDiagonallyUpAndRight},
      //  {"Infected chase soldier diagonally up and left", testMapChaseInfectedDiagonallyUpAndLeft},
      //  {"Infected chase soldier diagonally down and right", testMapChaseInfectedDiagonallyDownAndRight},
      //  {"Infected chase soldier diagonally down and left", testMapChaseInfectedDiagonallyDownAndLeft},

        {"Infected chase soldier up", testMapChaseInfectedUp},
        {"Infected chase soldier down", testMapChaseInfectedDown},
        {"Infected chase soldier right", testMapChaseInfectedRight},
        {"Infected chase soldier left", testMapChaseInfectedLeft},
        {NULL, NULL},

};

