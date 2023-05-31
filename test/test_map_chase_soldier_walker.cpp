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
#define WALKER_SPEED 1
#define MOVEMENTS_PER_CELL 15
#define MOV_NEEDED_TO_WALK_ALL_CELL 14
// ***************************************** Movimiento diagonal *******************************************8

void testMapChaseWalkerDiagonallyUpAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Walker walker(5,5, WALKER_SPEED);
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

void testMapChaseWalkerDiagonallyUpAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    Walker walker(5,5);
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

void testMapChaseWalkerDiagonallyDownAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 8);
    map.add_soldier(&soldier, 8, 8);

    Walker walker(5,5);
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

void testMapChaseWalkerDiagonallyDownAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Walker walker(5,5);
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

void testMapChaseWalkerUp() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5 * MOVEMENTS_PER_CELL, 5 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5 * MOVEMENTS_PER_CELL,8 * MOVEMENTS_PER_CELL, WALKER_SPEED);
    map.add_zombie(&walker, 5, 8);

    for (int i = 0; i < 1; i++) {
        map.chase_soldiers(i);
    }
    GameObject* walker1 = map.get_object(5, 7);
    GameObject* walker2 = map.get_object(6, 7);

    GameObject* old_pos1= map.get_object(5, 8);
    GameObject* old_pos2 = map.get_object(6, 8);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

void testMapChaseWalkerDown() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5 * MOVEMENTS_PER_CELL, 5 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5 * MOVEMENTS_PER_CELL,1 * MOVEMENTS_PER_CELL, WALKER_SPEED);
    map.add_zombie(&walker, 5, 1);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    GameObject* walker1 = map.get_object(5, 2);
    GameObject* walker2 = map.get_object(6, 2);

    GameObject* old_pos1= map.get_object(5, 1);
    GameObject* old_pos2 = map.get_object(6, 1);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);
}

//********************************** Right and Left **********************************************//

void testMapChaseWalkerRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5 * MOVEMENTS_PER_CELL, 5 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(2 * MOVEMENTS_PER_CELL,5 * MOVEMENTS_PER_CELL, WALKER_SPEED);
    map.add_zombie(&walker, 2, 5);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    GameObject* walker1 = map.get_object(3, 5);
    GameObject* walker2 = map.get_object(4, 5);

    GameObject* old_pos1= map.get_object(2, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMapChaseWalkerLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5 * MOVEMENTS_PER_CELL, 5 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(8 * MOVEMENTS_PER_CELL,5 * MOVEMENTS_PER_CELL);
    map.add_zombie(&walker, 8, 5);

    map.chase_soldiers(1);

    GameObject* walker1 = map.get_object(7, 5);
    GameObject* walker2 = map.get_object(8, 5);

    GameObject* old_pos1= map.get_object(9, 5);

    TEST_CHECK(walker1 != nullptr);
    TEST_CHECK(walker2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

TEST_LIST = {
      //  {"Walker chase soldier diagonally up and right", testMapChaseWalkerDiagonallyUpAndRight},
      //  {"Walker chase soldier diagonally up and left", testMapChaseWalkerDiagonallyUpAndLeft},
      //  {"Walker chase soldier diagonally down and right", testMapChaseWalkerDiagonallyDownAndRight},
      //  {"Walker chase soldier diagonally down and left", testMapChaseWalkerDiagonallyDownAndLeft},

        {"Walker chase soldier up", testMapChaseWalkerUp},
        {"Walker chase soldier down", testMapChaseWalkerDown},
        {"Walker chase soldier right", testMapChaseWalkerRight},
        {"Walker chase soldier left", testMapChaseWalkerLeft},
        {NULL, NULL},

};

