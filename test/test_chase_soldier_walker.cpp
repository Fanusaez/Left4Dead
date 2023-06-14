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
// ***************************************** Movimiento diagonal *******************************************//

void testChaseInfectedDiagonallyUpAndRightFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 2, 0);
     bool added_soldier = map.add_soldier(&soldier, 8, 2);

    Infected walker(5,5, map);
     bool added_walker = map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 1000; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == (7 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 2 * MOVEMENTS_PER_CELL);
    TEST_CHECK(added_soldier == true);
    TEST_CHECK(added_walker == true);
}


void testChaseInfectedDiagonallyUpAndLeftFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 1 , 3, 0 );
    map.add_soldier(&soldier, 1, 3);

    Infected walker(5 ,7 , map);
    map.add_zombie(&walker, 5, 7);

    for (int i = 0; i < 500; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);
}

void testChaseInfectedDiagonallyDownAndRightFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 8, 0);
    map.add_soldier(&soldier, 8, 8);

    Infected walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 7 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}


void testChaseInfectedDiagonallyDownAndLeftFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2 , 8, 0 );
    map.add_soldier(&soldier, 2, 8);

    Infected walker(5 ,5 , map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}

// ***************************************** Movimiento Up and Down *******************************************//

void testChaseInfectedUp() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5 ,8 , map);
    map.add_zombie(&walker, 5, 8);

    map.chase_soldiers(1);

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 5 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL - 1);
}

void testChaseInfectedUpFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5 ,8 , map);
    map.add_zombie(&walker, 5, 8);

    for (int i = 0; i < 105; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }
    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 5 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 6 * MOVEMENTS_PER_CELL);
}

void testChaseInfectedDown() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5 ,1 , map);
    map.add_zombie(&walker, 5, 1);

    map.chase_soldiers(1);

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 5 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 1 * MOVEMENTS_PER_CELL + 1);
}

void testChaseInfectedDownFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(5 ,1 , map);
    map.add_zombie(&walker, 5, 1);

    for (int i = 0; i < 105; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 5 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 4 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

// ***************************************** Movimiento Right and Left *******************************************//

void testChaseInfectedRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(2 ,5 , map);
    map.add_zombie(&walker, 2, 5);

    map.chase_soldiers(1);

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL + 1);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

void testChaseInfectedRightSideToSide() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8 , 5, 0 );
    map.add_soldier(&soldier, 8, 5);

    Infected walker(2 ,5 , map);
    map.add_zombie(&walker, 2, 5);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }
    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 7 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}


void testChaseInfectedLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5 , 5, 0 );
    map.add_soldier(&soldier, 5, 5);

    Infected walker(8 ,5 , map);
    map.add_zombie(&walker, 8, 5);

    map.chase_soldiers(1);

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL - 1);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

void testChaseInfectedLeftSideToSide() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 1 , 5, 0 );
    map.add_soldier(&soldier, 1, 5);

    Infected walker(8 ,5 , map);
    map.add_zombie(&walker, 8, 5);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers(i);
    }
    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

void testInfectedKillsSoldierAndStartsChasingOtherSoldier() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 0, 4, 0);
    map.add_soldier(&soldier1, 0, 4);

    Soldier soldier2(scout2, map, 5 , 5, 0);
    map.add_soldier(&soldier2, 5, 5);

    Infected walker(9 ,5 , map);
    map.add_zombie(&walker, 9, 5);

    for (int i = 0; i < 200; i++) { // enough to encounter the soldier face to face en 5 parara
        map.update(i);
    }

    std::int16_t sold1_health = soldier1.get_health();
    std::int16_t sold2_health = soldier2.get_health();

    TEST_CHECK(sold1_health <= 0);
    TEST_CHECK(sold2_health <= 0);
}


TEST_LIST = {
        {"Infected chase soldier diagonally up and right ends face to face", testChaseInfectedDiagonallyUpAndRightFaceToFace},
        {"Infected chase soldier diagonally up and left ends face to face", testChaseInfectedDiagonallyUpAndLeftFaceToFace},
        {"Infected chase soldier diagonally down and right ends face to face", testChaseInfectedDiagonallyDownAndRightFaceToFace},
        {"Infected chase soldier diagonally down and left ends face to face", testChaseInfectedDiagonallyDownAndLeftFaceToFace},

        {"Infected chase soldier up", testChaseInfectedUp},
        {"Infected chase soldier down", testChaseInfectedDown},

        {"Infected chase soldier right", testChaseInfectedRight},
        {"Infected chase soldier left", testChaseInfectedLeft},

        {"Infected chase soldier up face to face", testChaseInfectedUpFaceToFace},
        {"Infected chase soldier down face to face ", testChaseInfectedDownFaceToFace},

        {"Infected chase soldier right side to side", testChaseInfectedRightSideToSide},
        {"Infected chase soldier left side to side", testChaseInfectedLeftSideToSide},
        {"Infected kill soldier1 and continue to chase soldier2", testInfectedKillsSoldierAndStartsChasingOtherSoldier},
        {NULL, NULL},

};
