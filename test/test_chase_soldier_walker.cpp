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
#define WALKER_SPEED 0.3
// ***************************************** Movimiento diagonal *******************************************//

void testChaseWalkerDiagonallyUpAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    const float epsilon = 0.001; // Valor de tolerancia

    float received_numered_x = x_pos_walk;
    float expected_number_x = 5 + WALKER_SPEED;
    float received_numered_y = y_pos_walk;
    float expected_number_y = 5 - WALKER_SPEED;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDiagonallyUpAndRightFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 30; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    const float epsilon = 0.001; // Valor de tolerancia
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;
    float received_numered_x = x_pos_walk;
    float expected_number_x = 8;
    float received_numered_y = y_pos_walk;
    float expected_number_y = 3.2;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDiagonallyUpAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    std::int16_t x_pos_walk = walker.get_x();
    std::int16_t y_pos_walk = walker.get_y();

    TEST_CHECK(x_pos_walk == 4);
    TEST_CHECK(y_pos_walk == 4);
}

void testChaseWalkerDiagonallyUpAndLeftFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    Walker walker(5,7);
    map.add_zombie(&walker, 5, 7);

    for (int i = 0; i < 30; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;
    const float epsilon = 0.001; // Valor de tolerancia

    float received_numered_x = x_pos_walk;
    float expected_number_x = 1.1;
    float received_numered_y = y_pos_walk;
    float expected_number_y = 4.3;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDiagonallyDownAndRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 8);
    map.add_soldier(&soldier, 8, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    std::int16_t x_pos_walk = walker.get_x();
    std::int16_t y_pos_walk = walker.get_y();

    TEST_CHECK(x_pos_walk == 6);
    TEST_CHECK(y_pos_walk == 6);
}

void testChaseWalkerDiagonallyDownAndRightFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 8);
    map.add_soldier(&soldier, 8, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 31; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
   // std::cout << y_pos_walk;
    const float epsilon = 0.001; // Valor de tolerancia

    float received_numered_x = x_pos_walk;
    float expected_number_x = 8;
    float received_numered_y = y_pos_walk;
    float expected_number_y = 7.7;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDiagonallyDownAndLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    std::int16_t x_pos_walk = walker.get_x();
    std::int16_t y_pos_walk = walker.get_y();

    TEST_CHECK(x_pos_walk == 4);
    TEST_CHECK(y_pos_walk == 6);
}

void testChaseWalkerDiagonallyDownAndLeftFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 31; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;
    const float epsilon = 0.001; // Valor de tolerancia

    float received_numered_x = x_pos_walk;
    float expected_number_x = 2;
    float received_numered_y = y_pos_walk;
    float expected_number_y = 7.7;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

// ***************************************** Movimiento Up and Down *******************************************//

void testChaseWalkerUp() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5,8);
    map.add_zombie(&walker, 5, 8);

    for (int i = 0; i < 3; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia
    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float received_numered_y = y_pos_walk;
    float expected_number_y = 7.1;

    TEST_CHECK(x_pos_walk == 5);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerUpFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5,8);
    map.add_zombie(&walker, 5, 8);

    for (int i = 0; i < 15; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia
    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float received_numered_y = y_pos_walk;
    float expected_number_y = 6.2;

    TEST_CHECK(x_pos_walk == 5);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDown() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5,1);
    map.add_zombie(&walker, 5, 1);

    for (int i = 0; i < 4; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia
    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float received_numered_y = y_pos_walk;
    float expected_number_y = 2.2;

    TEST_CHECK(x_pos_walk == 5);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testChaseWalkerDownFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(5,1);
    map.add_zombie(&walker, 5, 1);

    for (int i = 0; i < 20; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia
    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();
    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float received_numered_y = y_pos_walk;
    float expected_number_y = 4.9;

    TEST_CHECK(x_pos_walk == 5);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

// ***************************************** Movimiento Right and Left *******************************************//

void testChaseWalkerRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(2,5);
    map.add_zombie(&walker, 2, 5);

    for (int i = 0; i < 4; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float expected_number_x = 3.2;

    TEST_CHECK(fabs(expected_number_x - x_pos_walk) < epsilon);
    TEST_CHECK(y_pos_walk == 5);
}

void testChaseWalkerRightSideToSide() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 5);
    map.add_soldier(&soldier, 8, 5);

    Walker walker(2,5);
    map.add_zombie(&walker, 2, 5);

    for (int i = 0; i < 20; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float expected_number_x = 6.8;

    TEST_CHECK(fabs(expected_number_x - x_pos_walk) < epsilon);
    TEST_CHECK(y_pos_walk == 5);
}


void testChaseWalkerLeft() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    Walker walker(8,5);
    map.add_zombie(&walker, 8, 5);

    for (int i = 0; i < 4; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float expected_number_x = 7.1;

    TEST_CHECK(fabs(expected_number_x - x_pos_walk) < epsilon);
    TEST_CHECK(y_pos_walk == 5);
}

void testChaseWalkerLeftSideToSide() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 5);
    map.add_soldier(&soldier, 1, 5);

    Walker walker(8,5);
    map.add_zombie(&walker, 8, 5);

    for (int i = 0; i < 30; i++) { // enough to encounter the soldier face to face en 5 parara
        map.chase_soldiers();
    }
    const float epsilon = 0.001; // Valor de tolerancia

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    //std::cout << x_pos_walk;
    //std::cout << y_pos_walk;

    float expected_number_x = 3.2;

    TEST_CHECK(fabs(expected_number_x - x_pos_walk) < epsilon);
    TEST_CHECK(y_pos_walk == 5);
}


TEST_LIST = {
        //{"Walker chase soldier diagonally up and right", testChaseWalkerDiagonallyUpAndRight},
        {"Walker chase soldier diagonally up and right ends face to face", testChaseWalkerDiagonallyUpAndRightFaceToFace},
       // {"Walker chase soldier diagonally up and left", testChaseWalkerDiagonallyUpAndLeft},
        {"Walker chase soldier diagonally up and left ends face to face", testChaseWalkerDiagonallyUpAndLeftFaceToFace},
       // {"Walker chase soldier diagonally down and right", testChaseWalkerDiagonallyDownAndRight},
        {"Walker chase soldier diagonally down and right ends face to face", testChaseWalkerDiagonallyDownAndRightFaceToFace},
      //  {"Walker chase soldier diagonally down and left", testChaseWalkerDiagonallyDownAndLeft},
        {"Walker chase soldier diagonally down and left ends face to face", testChaseWalkerDiagonallyDownAndLeftFaceToFace},

        {"Walker chase soldier up", testChaseWalkerUp},
        {"Walker chase soldier down", testChaseWalkerDown},

        {"Walker chase soldier right", testChaseWalkerRight},
        {"Walker chase soldier left", testChaseWalkerLeft},

        {"Walker chase soldier up", testChaseWalkerUpFaceToFace},
        {"Walker chase soldier down", testChaseWalkerDownFaceToFace},

        {"Walker chase soldier right", testChaseWalkerRightSideToSide},
        {"Walker chase soldier left", testChaseWalkerLeftSideToSide},
        {NULL, NULL},

};
