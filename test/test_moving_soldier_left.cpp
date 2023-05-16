#include <cstdint>
#include "acutest.h"
#include "../src/soldier.h"
#include "../src/walker.h"
#include "../src/map.h"
#include "../src/game_object.h"
#include "../src/scout.h"
#include "../src/weapon.h"
#include "idf.h"

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

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 2);
    TEST_CHECK(y_pos == 8);
}

void testMoveSoldierLeftBeginningOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 0, 3);
    map.add_soldier(&soldier, 0, 3);

    soldier.move_left();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 0);
    TEST_CHECK(y_pos == 3);
}

void testNotMoveSoldierLeftForCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(1,7);
    map.add_zombie(&walker, 1, 7);

    soldier.move_left();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 7);
}


void testMoveSoldierLeftWithZombieClose(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9);
    map.add_zombie(&walker, 4, 9);

    soldier.move_left();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 2);
    TEST_CHECK(y_pos == 8);
}


TEST_LIST = {
        {"Move soldier 1 position Left",testMoveSoldierLeft},
        {"Move soldier 1 position on limit of map",testMoveSoldierLeftBeginningOfMap},
        {"Move soldier 1 position Left not possible for walker",testNotMoveSoldierLeftForCollisionWithZombie},
        {"Move soldier 1 position Left close to a zombie", testMoveSoldierLeftWithZombieClose},
        {NULL, NULL},
};




