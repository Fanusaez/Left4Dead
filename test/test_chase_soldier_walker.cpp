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

// ***************************************** Movimiento diagonal *******************************************8

void testChaseWalkerDiagonally(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 3);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers();

    std::int16_t x_pos_walk = walker.get_x();
    std::int16_t y_pos_walk = walker.get_y();
    std::cout << y_pos_walk;
    TEST_CHECK(x_pos_walk == 6);
    TEST_CHECK(y_pos_walk == 4);
}

TEST_LIST = {
        {"", testChaseWalkerDiagonally},
        {NULL, NULL},

};
