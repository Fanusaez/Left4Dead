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

void testMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_up();

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 8 - SOLDIER_SPEED;

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testNotMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(3,7);
    map.add_zombie(&walker, 3, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}

void testNotMoveSoldierUpCrashesPartiallyWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,7);
    map.add_zombie(&walker, 4, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}

void testNotMoveSoldierUpCrashesPartiallyWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(2,7);
    map.add_zombie(&walker, 2, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}

void testMoveSoldierUpUntilEndOfTheMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 2, SOLDIER_SPEED);
    map.add_soldier(&soldier, 3, 2);

    for (float i = 0; i < 30; i++) {
        soldier.move_up();
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 0.4;

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

void testMoveSoldierUpUntilEndOfTheMap2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9, SOLDIER_SPEED);
    map.add_soldier(&soldier, 8, 9);

    for (float i = 0; i < 50; i++) {
        soldier.move_up(i);
    }

    float x_pos = soldier.get_x_position();
    float y_pos = soldier.get_y_position();

    std::cout << y_pos;

    const float epsilon = 0.001; // Valor de tolerancia
    float received_numered = y_pos;
    float expected_number = 0.4;

    TEST_CHECK(x_pos == 8);
    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
}

TEST_LIST = {
        {"Move soldier 1 position up",testMoveSoldierUp},
        {"Move soldier 1 position up goes not possible for walker totally aligned",testNotMoveSoldierUp},
        {"Move soldier 1 position up goes not possible for walker partially aligned (right side)", testNotMoveSoldierUpCrashesPartiallyWithZombie},
        {"Move soldier 1 position up goes not possible for walker partially aligned(left side)", testNotMoveSoldierUpCrashesPartiallyWithZombie2},
        {"Move soldier up until end of the map",testMoveSoldierUpUntilEndOfTheMap},
        {"Move soldier up until end of the map",testMoveSoldierUpUntilEndOfTheMap2},
        {NULL, NULL},
};


