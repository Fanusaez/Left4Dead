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
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1

void testMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_up();

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testNotMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    Infected walker(3 ,7, map);
    map.add_zombie(&walker, 3, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == (3 * MOVEMENTS_PER_CELL));
    TEST_CHECK(y_pos == (8 * MOVEMENTS_PER_CELL));
}

void testNotMoveSoldierUpCrashesPartiallyWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);
    for (int i = 0; i < MOV_NEEDED_TO_WALK_ALL_CELL; i++) {
        soldier.move_right();
    }

    Infected walker(3,7, map);
    map.add_zombie(&walker, 3, 7);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == ((3 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL));
    TEST_CHECK(y_pos == (8 * MOVEMENTS_PER_CELL));
}

void testMoveSoldierWithZombieClose(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 8, 0);
    map.add_soldier(&soldier, 2, 8);

    for (int i = 0; i < MOV_NEEDED_TO_WALK_ALL_CELL; i++) {
        soldier.move_right();
    }

    Infected walker(3,7, map);
    map.add_zombie(&walker, 3, 7);

    soldier.move_up();

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    std::cout << x_pos << std::endl;
    std::cout << y_pos << std::endl;

    TEST_CHECK(x_pos == (2 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL);
    TEST_CHECK(y_pos == (7 * MOVEMENTS_PER_CELL) + MOV_NEEDED_TO_WALK_ALL_CELL);
}

void testMoveSoldierUpUntilEndOfTheMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 2, 0);
    map.add_soldier(&soldier, 3, 2);

    for (float i = 0; i < 1000; i++) {
        soldier.move_up();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 0);
}

void testMoveSoldierUpUntilEndOfTheMap2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    for (int i = 0; i < 1000; i++) {
        soldier.move_up();
    }

    std::int16_t x_pos = soldier.get_x_pos();
    std::int16_t y_pos = soldier.get_y_pos();
    std::cout << y_pos;
    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 0);
}

TEST_LIST = {
        {"Move soldier 1 position up",testMoveSoldierUp},
        {"Move soldier 1 position up goes not possible for walker totally aligned",testNotMoveSoldierUp},
        {"Move soldier 1 position up goes not possible for walker partially aligned (right side)", testNotMoveSoldierUpCrashesPartiallyWithZombie},
        {"Move soldier 1 position up with infected close", testMoveSoldierWithZombieClose},
        {"Move soldier up until end of the map",testMoveSoldierUpUntilEndOfTheMap},
        {"Move soldier up until end of the map",testMoveSoldierUpUntilEndOfTheMap2},
        {NULL, NULL},
};


