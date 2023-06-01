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
#define MOVEMENTS_PER_CELL 15
#define MOV_NEEDED_TO_WALK_ALL_CELL 14
#define SOLDIER_SPEED 1

void testMoveSoldierLeft(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_left();

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}

void testMoveSoldierLeftBeginningOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 3);
    map.add_soldier(&soldier, 1, 3);

    for (float i = 0; i < 20; i++){
        soldier.move_left();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 0);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);
}

void testNotMoveSoldierLeftForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(1,7, map);
    map.add_zombie(&walker, 1, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_left();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL);
}


void testMoveSoldierLeftAllTheWay(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 5);
    map.add_soldier(&soldier, 5, 5);

    for (int i = 0; i < 100; i++) {
        soldier.move_left(i);
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 0);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

TEST_LIST = {
        {"Move soldier 1 position Left",testMoveSoldierLeft},
        {"Move soldier 1 position on limit of map",testMoveSoldierLeftBeginningOfMap},
        {"Move soldier 1 position Left not possible for walker",testNotMoveSoldierLeftForCollisionWithZombie},
        {"Move soldier from end to beginning", testMoveSoldierLeftAllTheWay},
        {NULL, NULL},
};




