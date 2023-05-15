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


void testMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

   soldier.move_up();

   std::uint16_t x_pos = soldier.get_x_position();
   std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 7);
}

void testMoveSoldierUpGoesToEndOfMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 0);
    map.add_soldier(&soldier, 3, 0);

    soldier.move_up();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 9);
}

void testNotMoveSoldierUp(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(3,7);
    map.add_zombie(&walker, 3, 7);

    soldier.move_up();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}


TEST_LIST = {
        {"Move soldier 1 position up",testMoveSoldierUp},
        {"Move soldier 1 position up goes to the other side of map",testMoveSoldierUpGoesToEndOfMap},
        {"Move soldier 1 position up goes not possible for walker",testNotMoveSoldierUp},
        {NULL, NULL},
};


