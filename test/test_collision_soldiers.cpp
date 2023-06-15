#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define UP -1
#define DOWN 1
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1

// ************************************ Colisiones eje Y *******************************************

void testCollisionAmongSoldiers(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 5, 5, 0);
    map.add_soldier(&soldier1, 5, 5);

    Soldier soldier2(scout2, map, 5, 6, 0);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 6);
     map.empty_vectors();
}

void testCollisionAmongSoldiers2(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 5, 5, 0);
    map.add_soldier(&soldier1, 5, 5);

    soldier1.move_right();

    Soldier soldier2(scout2, map, 5, 6, 0);
    map.add_soldier(&soldier2, 5, 6);

    for (int i = 0; i < 50; i++) {
        soldier2.move_up();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 6);
     map.empty_vectors();
}

void testCollisionAmongSoldiers3(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 4, 5, 0);
    map.add_soldier(&soldier1, 4, 5);

    Soldier soldier2(scout2, map, 4, 6, 0);
    map.add_soldier(&soldier2, 4, 6);

    soldier2.move_right();

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
    TEST_CHECK(x_matrix_pos2 == 4);
    TEST_CHECK(y_matrix_pos2 == 6);
     map.empty_vectors();
}

// ************************************ Colisiones eje X *******************************************

void testCollisionAmongSoldiers4(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 4, 5, 0);
    map.add_soldier(&soldier1, 4, 5);

    Soldier soldier2(scout2, map, 5, 5, 0);
    map.add_soldier(&soldier2, 5, 5);

    for (int i = 0; i < 50; i++) {
        soldier2.move_left();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 5);
     map.empty_vectors();
}

void testCollisionAmongSoldiers5(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 4, 5, 0);
    map.add_soldier(&soldier1, 4, 5);


    Soldier soldier2(scout2, map, 5, 5, 0);
    map.add_soldier(&soldier2, 5, 5);

    for (int i = 0; i < 50; i++) {
        soldier1.move_right();
    }

    std::int16_t x_matrix_pos = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos = soldier2.get_y_matrix_pos();

    TEST_CHECK(x_matrix_pos == 5);
    TEST_CHECK(y_matrix_pos == 5);
     map.empty_vectors();
}

void testCollisionAmongSoldiers6(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, 4, 5, 0);
    map.add_soldier(&soldier1, 4, 5);

    Soldier soldier2(scout2, map, 5, 5, 0);
    map.add_soldier(&soldier2, 5, 5);


    for (int i = 0; i < 20; i++) {
        soldier1.move_right();
    }

    for (int i = 0; i < 50; i++) {
        soldier2.move_left();
    }

    std::int16_t x_matrix_pos1 = soldier1.get_x_matrix_pos();
    std::int16_t y_matrix_pos1 = soldier1.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos1 == 4);
    TEST_CHECK(y_matrix_pos1 == 5);

    std::int16_t x_matrix_pos2 = soldier2.get_x_matrix_pos();
    std::int16_t y_matrix_pos2 = soldier2.get_y_matrix_pos();
    TEST_CHECK(x_matrix_pos2 == 5);
    TEST_CHECK(y_matrix_pos2 == 5);
     map.empty_vectors();
}


TEST_LIST = {
        {"Testing collision going up", testCollisionAmongSoldiers},
        {"Testing collision going up 2", testCollisionAmongSoldiers2},
        {"Testing collision going up 3", testCollisionAmongSoldiers3},
        {"Testing collision going left 4", testCollisionAmongSoldiers4},
        {"Testing collision going right 5", testCollisionAmongSoldiers5},
        {"Testing collision going right-left 6", testCollisionAmongSoldiers6},


        {NULL, NULL}
};