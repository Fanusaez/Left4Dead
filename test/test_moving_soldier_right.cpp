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

void testMoveSoldierRight(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_right();

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 3 + SOLDIER_SPEED;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 8);
}

void testMoveSoldierRightEndOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, MAP_SIZE_X - 2, 3, SOLDIER_SPEED);
    map.add_soldier(&soldier, MAP_SIZE_X - 2, 3);

    for (float i = 0; i < 10; i++){
        soldier.move_right();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 9 - SOLDIER_SPEED;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 3);

}

void testNotMoveSoldierRightForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(5,7);
    map.add_zombie(&walker, 5, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_right();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    // recordar, 4 Es la posicion de la otra pos del soldado
    float expected_number = 4 - SOLDIER_SPEED;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 7);
}


void testMoveSoldierRightWithZombieClose() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9);
    map.add_zombie(&walker, 4, 9);

    for (int i = 0; i < 30; i++){
        soldier.move_right();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 9 - SOLDIER_SPEED;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 8);
}


TEST_LIST = {
        {"Move soldier 1 position right",testMoveSoldierRight},
        {"Move soldier 1 position on limit of map",testMoveSoldierRightEndOfMap},
        {"Move soldier 1 position right not possible for walker",testNotMoveSoldierRightForCollisionWithZombie},
        {"Move soldier 1 position right close to a zombie", testMoveSoldierRightWithZombieClose},
        {NULL, NULL},
};



