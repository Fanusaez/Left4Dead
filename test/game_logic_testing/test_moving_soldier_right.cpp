#include <cstdint>
#include <iostream>
#include "../acutest.h"
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
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1
#define SOLDIER_SPEED 1

void testMoveSoldierRight() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_right();

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL + SOLDIER_SPEED);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
     map.empty_vectors();
}

void testMoveSoldierRightEndOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 3, 0);
    map.add_soldier(&soldier, 5, 3);

    for (float i = 0; i < 100; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 9 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);
    map.empty_vectors();
}

void testNotMoveSoldierRightForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    Infected walker(5, 7, 0, map, 0, 0);
    map.add_zombie(&walker, 5, 7);

    for (float i = 0; i < 100; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 4 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL);
     map.empty_vectors();
}


void testMoveSoldierRightWithZombieClose() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    Infected walker(4, 9, 0, map, 0, 0);
    map.add_zombie(&walker, 4, 9);

    for (int i = 0; i < 150; i++){
        soldier.move_right();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 9 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
     map.empty_vectors();
}

void testMoveSoldierRightAllTheWay(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 0, 0, 0);
    map.add_soldier(&soldier, 0, 0);

    for (int i = 0; i < 200; i++) {
        soldier.move_right(i);
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 9 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == 0);
     map.empty_vectors();
}

TEST_LIST = {
        {"Move soldier 1 position right",testMoveSoldierRight},
        {"Move soldier 1 position on limit of map",testMoveSoldierRightEndOfMap},
        {"Move soldier 1 position right not possible for walker",testNotMoveSoldierRightForCollisionWithZombie},
        {"Move soldier 1 position right close to a zombie", testMoveSoldierRightWithZombieClose},
        {"Move soldier from beginning to end",testMoveSoldierRightAllTheWay},
        {NULL, NULL},
};



