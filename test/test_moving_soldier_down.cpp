#include <cstdint>
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


void testMoveSoldierDown(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_down();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 9);
}

void testMoveSoldierDownGoesToBeginning() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, MAP_SIZE_Y - 1);
    map.add_soldier(&soldier, 3, MAP_SIZE_Y - 1);

    soldier.move_down();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 0);
}

void testNotMoveSoldierDownForCompleteCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    soldier.move_down();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 7);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9);
    map.add_zombie(&walker, 4, 9);

    soldier.move_down();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(2,9);
    map.add_zombie(&walker, 2, 9);

    soldier.move_down();

    std::uint16_t x_pos = soldier.get_x_position();
    std::uint16_t y_pos = soldier.get_y_position();

    TEST_CHECK(x_pos == 3);
    TEST_CHECK(y_pos == 8);
}


TEST_LIST = {
        {"Move soldier 1 position down",testMoveSoldierDown},
        {"Move soldier 1 position down goes to the other side of map",testMoveSoldierDownGoesToBeginning},
        {"Move soldier 1 position down goes not possible for walker totally aligned",testNotMoveSoldierDownForCompleteCollisionWithZombie},
        {"Move soldier 1 position down goes not possible for walker partially aligned (right side)", testNotMoveSoldierDownForPartialCollisionWithZombie},
        {"Move soldier 1 position down goes not possible for walker partially aligned(left side)", testNotMoveSoldierDownForPartialCollisionWithZombie2},
        {NULL, NULL},
};


