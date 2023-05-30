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

void testMoveSoldierDown(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL, 8 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 3, 8);

    for (int i = 0; i < MOV_NEEDED_TO_WALK_ALL_CELL; i++){
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3*MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == (9*MOVEMENTS_PER_CELL - 1));
}

void testMoveSoldierDownAtTheEndDoesNotMove() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL, (MAP_SIZE_Y - 1) * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 3, MAP_SIZE_Y - 1);

    for (int i = 0; i < 30; i++){
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == (10 * MOVEMENTS_PER_CELL) - 1);
}

void testNotMoveSoldierDownForCompleteCollisionWithZombie() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL, (7 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(3 * MOVEMENTS_PER_CELL,8 * MOVEMENTS_PER_CELL);
    map.add_zombie(&walker, 3, 8);

    for (float i = 0; i < 5; i++){ // con 5 se va a 8
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL, (8 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL - 5);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4 * MOVEMENTS_PER_CELL,9 * MOVEMENTS_PER_CELL);
    map.add_zombie(&walker, 4, 9);

    for (float i = 0; i < 10; i++){
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL, (8 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(2 * MOVEMENTS_PER_CELL,9 * MOVEMENTS_PER_CELL);
    map.add_zombie(&walker, 2, 9);

    for (float i = 0; i < 10; i++){
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testMoveSoldierDownUntilTheEnd() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3 * MOVEMENTS_PER_CELL , 8 * MOVEMENTS_PER_CELL);
    map.add_soldier(&soldier, 3, 8);

    for (int i = 0; i < 150; i++){
        soldier.move_down();
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 9 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testMoveSoldierDownUntilTheEnd2() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 0, 0);
    map.add_soldier(&soldier, 0, 0);

    for (int i = 0; i < 150; i++){
        soldier.move_down(i);
    }

    std::int16_t x_pos = soldier.get_x_position();
    std::int16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 0 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 9 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
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


