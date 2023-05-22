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


void testMoveSoldierLeft(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);


    soldier.move_left();


    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 2.8;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 8);
}

void testMoveSoldierLeftBeginningOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    for (float i = 0; i < 20; i++){
        soldier.move_left();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 0.4; // ver

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 3);
}

void testNotMoveSoldierLeftForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(1,7);
    map.add_zombie(&walker, 1, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_left();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();
    std::cout << x_pos;

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = x_pos;
    float expected_number = 3;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos == 7);
}


TEST_LIST = {
        {"Move soldier 1 position Left",testMoveSoldierLeft},
        {"Move soldier 1 position on limit of map",testMoveSoldierLeftBeginningOfMap},
        {"Move soldier 1 position Left not possible for walker",testNotMoveSoldierLeftForCollisionWithZombie},
        {NULL, NULL},
};




