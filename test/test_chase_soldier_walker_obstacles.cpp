#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
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
#define MOVEMENTS_PER_CELL 15
#define MOV_NEEDED_TO_WALK_ALL_CELL 14

void testWalkerChaseSoldierdiagonallyUpAndRightWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Obstacle obstacle(5, 5, 0);
    map.add_obstacle(&obstacle, 5, 5);

    Walker walker(5,6, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 6 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 6 * MOVEMENTS_PER_CELL);
}

void testWalkerChaseSoldierdiagonallyUpAndRightWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8 , 2 );
    map.add_soldier(&soldier, 8, 2);

    Obstacle obstacle(5 , 5 , 0);
    map.add_obstacle(&obstacle, 5, 5);

    Walker walker(5 ,6 , map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 100; i++) {
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 8 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);
}

void testWalkerChaseSoldierdiagonallyUpAndLeftWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 2);
    map.add_soldier(&soldier, 1, 2);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 4 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 6 * MOVEMENTS_PER_CELL);
}

void testWalkerChaseSoldierdiagonallyUpLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 100; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 3 * MOVEMENTS_PER_CELL);
}

void testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 6);

    Walker walker(5,5, map);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }

    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 4 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 5 * MOVEMENTS_PER_CELL);
}

void testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Obstacle osbtacle(5, 5, 0);
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, map);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 140; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers(i);
    }
    std::int16_t x_pos = walker.get_x_pos();
    std::int16_t y_pos = walker.get_y_pos();

    TEST_CHECK(x_pos == 2 * MOVEMENTS_PER_CELL);
    TEST_CHECK(y_pos == 7 * MOVEMENTS_PER_CELL + MOV_NEEDED_TO_WALK_ALL_CELL);
}

TEST_LIST = {
        {"Walker avoid the obstacle and moves to chase the soldier", testWalkerChaseSoldierdiagonallyUpAndRightWithObstacle},
        {"Walker avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testWalkerChaseSoldierdiagonallyUpAndRightWithObstacleFaceToFace},
        {"Walker avoid the obstacle and moves to chase the soldier", testWalkerChaseSoldierdiagonallyUpAndLeftWithObstacle},
        {"Walker avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testWalkerChaseSoldierdiagonallyUpLeftWithObstacleFaceToFace},
        {"Walker avoid the obstacle and moves to chase the soldier", testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacle},
        {"Walker avoid the obstacle and moves to chase the soldier and meets with soldier ftf", testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacleFaceToFace},
        {NULL, NULL},
};