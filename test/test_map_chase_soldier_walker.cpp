#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/scout.h"
#include "game_logic/weapon.h"
#include "game_logic/idf.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10

// ***************************************** Movimiento diagonal *******************************************8

void testMapChaseWalkerDiagonallyUpAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    GameObject* walker1 = map.get_object(6, 4);
    GameObject* walker2 = map.get_object(7, 4);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseWalkerDiagonallyUpAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    GameObject* walker1 = map.get_object(4, 4);
    GameObject* walker2 = map.get_object(5, 4);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseWalkerDiagonallyDownAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 8);
    map.add_soldier(&soldier, 8, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    GameObject* walker1 = map.get_object(6, 6);
    GameObject* walker2 = map.get_object(7, 6);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseWalkerDiagonallyDownAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    GameObject* walker1 = map.get_object(4, 6);
    GameObject* walker2 = map.get_object(5, 6);

    GameObject* old_pos1= map.get_object(5, 5);
    GameObject* old_pos2 = map.get_object(6, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}




TEST_LIST = {
        {"Walker chase soldier diagonally up and right", testMapChaseWalkerDiagonallyUpAndRight},
        {"Walker chase soldier diagonally up and left", testMapChaseWalkerDiagonallyUpAndLeft},
        {"Walker chase soldier diagonally down and right", testMapChaseWalkerDiagonallyDownAndRight},
        {"Walker chase soldier diagonally down and left", testMapChaseWalkerDiagonallyDownAndLeft},
        {NULL, NULL},

};
