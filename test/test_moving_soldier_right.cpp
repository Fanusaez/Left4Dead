#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/walker.h"
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

void testMoveSoldierRight(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_right();

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + SOLDIER_SPEED);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}

void testMoveSoldierRightEndOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, (MAP_SIZE_X - 2), 3);
    map.add_soldier(&soldier, MAP_SIZE_X - 2, 3);

    for (float i = 0; i < 15; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == (MAP_SIZE_X - 2) * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);

}

void testNotMoveSoldierRightForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(5,7, map);
    map.add_zombie(&walker, 5, 7);

    for (float i = 0; i < 100; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL);
}


void testMoveSoldierRightWithZombieClose() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9, map);
    map.add_zombie(&walker, 4, 9);

    for (int i = 0; i < 150; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}

void testMoveSoldierRightAllTheWay(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 0, 0);
    map.add_soldier(&soldier, 0, 0);

    for (int i = 0; i < 200; i++) {
        soldier.move_right(i);
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 0);
}

TEST_LIST = {
        {"Move soldier 1 position right",testMoveSoldierRight},
        {"Move soldier 1 position on limit of map",testMoveSoldierRightEndOfMap},
        {"Move soldier 1 position right not possible for walker",testNotMoveSoldierRightForCollisionWithZombie},
        {"Move soldier 1 position right close to a zombie", testMoveSoldierRightWithZombieClose},
        {"Move soldier from beginning to end",testMoveSoldierRightAllTheWay},
        {NULL, NULL},
};



