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
#define SOLDIER_SPEED 0.2

void testMoveSoldierDown(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    for (int i = 0; i < 3; i++){
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 8 + (SOLDIER_SPEED*3);

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

/*
 * Revisar
 */
void testMoveSoldierDownAtTheEndDoesNotMove() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, MAP_SIZE_Y - 1, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, MAP_SIZE_Y - 1);

    for (int i = 0; i < 30; i++){
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = MAP_SIZE_Y - SOLDIER_SPEED;
    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testNotMoveSoldierDownForCompleteCollisionWithZombie() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    for (float i = 0; i < 5; i++){ // con 5 se va a 8
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 8 - SOLDIER_SPEED;

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9);
    map.add_zombie(&walker, 4, 9);

    for (float i = 0; i < 10; i++){
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 9 - SOLDIER_SPEED;

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(2,9);
    map.add_zombie(&walker, 2, 9);

    for (float i = 0; i < 10; i++){
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 9 - SOLDIER_SPEED;

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}
/// BUG, REVISAR PQ SOLO AVANZA HASTA 9
void testMoveSoldierDownUntilTheEnd() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    for (int i = 0; i < 15; i++){
        soldier.move_down();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    double received_numered = y_pos;
    double expected_number =  9.8; /// deberia ser 9.8. hay un bug

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testMoveSoldierDownUntilTheEnd2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 0.0, 0.0);
    map.add_soldier(&soldier, 0, 0);

    for (int i = 0; i < 150; i++){
        soldier.move_down(i);
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();
    //std::cout << y_pos;
    const float epsilon = 0.001; // Valor de tolerancia
    double received_numered = y_pos;
    double expected_number =  9.8;

   TEST_CHECK(x_pos == 0);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}
TEST_LIST = {
        {"Move soldier 1 position down",testMoveSoldierDown},
        {"Move soldier 1 position down goes to the other side of map",testMoveSoldierDownAtTheEndDoesNotMove},
        {"Move soldier 1 position down goes not possible for walker totally aligned",testNotMoveSoldierDownForCompleteCollisionWithZombie},
        {"Move soldier 1 position down goes not possible for walker partially aligned (right side)", testNotMoveSoldierDownForPartialCollisionWithZombie},
        {"Move soldier 1 position down goes not possible for walker partially aligned(left side)", testNotMoveSoldierDownForPartialCollisionWithZombie2},
        {"Moves Soldier down until end of map", testMoveSoldierDownUntilTheEnd},
        {"Moves Soldier down until end of map from 0,0", testMoveSoldierDownUntilTheEnd2},
        {NULL, NULL},
};


