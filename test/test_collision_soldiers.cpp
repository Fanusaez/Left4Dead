#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define UP -1
#define DOWN 1
#define MOVEMENTS_PER_CELL 15
#define MOV_NEEDED_TO_WALK_ALL_CELL 14

void testCollisionAmongSoldiers(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout;
    Weapon* scout2 = new Scout;

    Soldier soldier1(scout1, map, 5, 5);
    map.add_soldier(&soldier1, 5, 5);

    Soldier soldier2(scout2, map, 5, 6);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 6);
}

void testCollisionAmongSoldiers2(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout;
    Weapon* scout2 = new Scout;

    Soldier soldier1(scout1, map, 4, 5);
    map.add_soldier(&soldier1, 4, 5);

    Soldier soldier2(scout2, map, 5, 6);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 6);
}

void testCollisionAmongSoldiers3(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout;
    Weapon* scout2 = new Scout;

    Soldier soldier1(scout1, map, 4, 5);
    map.add_soldier(&soldier1, 4, 5);

    Soldier soldier2(scout2, map, 5, 6);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 20; i++) {
        soldier1.move_down();
    }

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos1 = soldier1.get_x_matrix_pos();
    std::int16_t y_matrix_pos1 = soldier1.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos1 == 4);
    TEST_CHECK(y_matrix_pos1 == 5);

    std::int16_t x_matrix_pos2 = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos2 = soldier2.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos2 == 5);
    TEST_CHECK(y_matrix_pos2 == 6);
}

void testCollisionAmongSoldiers4(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout;
    Weapon* scout2 = new Scout;

    Soldier soldier1(scout1, map, 6, 5);
    map.add_soldier(&soldier1, 6, 5);

    Soldier soldier2(scout2, map, 5, 6);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 20; i++) {
        soldier1.move_down();
    }

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos1 = soldier1.get_x_matrix_pos();
    std::int16_t y_matrix_pos1 = soldier1.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos1 == 6);
    TEST_CHECK(y_matrix_pos1 == 5);

    std::int16_t x_matrix_pos2 = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos2 = soldier2.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos2 == 5);
    TEST_CHECK(y_matrix_pos2 == 6);
}

TEST_LIST = {
        {"Testing collision going up", testCollisionAmongSoldiers},
        {"Testing collision going up 2", testCollisionAmongSoldiers2},
        {"Testing collision going up 3", testCollisionAmongSoldiers3},
        {"Testing collision going up 4", testCollisionAmongSoldiers4},
        {NULL, NULL}
};