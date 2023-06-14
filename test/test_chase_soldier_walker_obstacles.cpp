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
#include "game_logic/obstacle.h"
#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define WALKER_SPEED 1
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1

void testInfectedChaseSoldierdiagonallyUpAndRightWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 2, 0);
    map.add_soldier(&soldier, 8, 2);

    Obstacle obstacle(5, 5, 0);
    map.add_obstacle(&obstacle, 5, 5);

    Infected walker(5, 6, 0, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 6 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 6 * MOVEMENTS_PER_CELL);
}

void testInfectedChaseSoldierdiagonallyUpAndRightWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 2, 0);
    map.add_soldier(&soldier, 8, 2);

    Obstacle obstacle(5 , 5 , 0);
    map.add_obstacle(&obstacle, 5, 5);

    Infected walker(5, 6, 0, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 100; i++) {
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL - 1);
    TEST_CHECK(y_pos == 2 * MOVEMENTS_PER_CELL);
}

void testInfectedChaseSoldierdiagonallyUpAndLeftWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 1, 2, 0);
    map.add_soldier(&soldier, 1, 2);

    Obstacle osbtacle(6, 4, 0);
    map.add_obstacle(&osbtacle, 6, 4);

    Infected walker(6, 5, 0, map);
    map.add_zombie(&walker, 6, 5);

    map.chase_soldiers(1);


    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 6 * MOVEMENTS_PER_CELL - 1);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

void testInfectedChaseSoldierdiagonallyUpLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 5);

    Infected walker(5, 6, 0, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 2 * MOVEMENTS_PER_CELL);
}


void testInfectedChaseSoldierdiagonallyDownAndLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 8, 0);
    map.add_soldier(&soldier, 2, 8);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 5);

    Infected walker(5, 6, 0, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 140; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }
    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 3 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 8 * MOVEMENTS_PER_CELL);
}

TEST_LIST = {
        {"Infected avoid the obstacle and moves to chase the soldier", testInfectedChaseSoldierdiagonallyUpAndRightWithObstacle},
        {"Infected avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testInfectedChaseSoldierdiagonallyUpAndRightWithObstacleFaceToFace},
        {"Infected avoid the obstacle and moves to chase the soldier", testInfectedChaseSoldierdiagonallyUpAndLeftWithObstacle},
        {"Infected avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testInfectedChaseSoldierdiagonallyUpLeftWithObstacleFaceToFace},
        {"Infected avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testInfectedChaseSoldierdiagonallyDownAndLeftWithObstacleFaceToFace},
        {NULL, NULL},
};