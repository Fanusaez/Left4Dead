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
#include "game_logic/obstacle.h"
#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define WALKER_SPEED 0.3

void testWalkerChaseSoldierdiagonallyUpAndRightWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, WALKER_SPEED);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 4; i++) {
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered = x_pos_walk;
    double expected_number =  6.2;

    TEST_CHECK(fabs(received_numered - expected_number) < epsilon);
    TEST_CHECK(y_pos_walk == 6);

    //map.chase_soldiers(); // moves diagonally upright

    //std::int16_t x_pos_walk2 = walker.get_x();
    //std::int16_t y_pos_walk2 = walker.get_y();

   // TEST_CHECK(x_pos_walk2 == 7);
    //TEST_CHECK(y_pos_walk2 == 5);
}

void testWalkerChaseSoldierdiagonallyUpAndRightWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 2);
    map.add_soldier(&soldier, 8, 2);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, WALKER_SPEED);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 30; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered_x = x_pos_walk;
    double expected_number_x =  8;

    double received_numered_y = y_pos_walk;
    double expected_number_y =  3.3;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testWalkerChaseSoldierdiagonallyUpAndLeftWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 1, 2);
    map.add_soldier(&soldier, 1, 2);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, WALKER_SPEED);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 30; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered_x = x_pos_walk;
    double expected_number_x =  1.1;

    double received_numered_y = y_pos_walk;
    double expected_number_y =  3.3;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);

    //map.chase_soldiers(); // moves diagonally upleft

    //std::int16_t x_pos_walk2 = walker.get_x();
    //std::int16_t y_pos_walk2 = walker.get_y();

    //TEST_CHECK(x_pos_walk2 == 3);
    //TEST_CHECK(y_pos_walk2 == 5);
}

void testWalkerChaseSoldierdiagonallyUpLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6, WALKER_SPEED);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 40; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered_x = x_pos_walk;
    double expected_number_x =  2;

    double received_numered_y = y_pos_walk;
    double expected_number_y =  3.3;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
}

void testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacle() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 6);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    for (int i = 0; i < 1; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered_x = x_pos_walk;
    double expected_number_x =  4.7;

    double received_numered_y = y_pos_walk;
    double expected_number_y = 5;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);

    //map.chase_soldiers(); // moves diagonally downleft

    //std::int16_t x_pos_walk2 = walker.get_x();
    //std::int16_t y_pos_walk2 = walker.get_y();

    //TEST_CHECK(x_pos_walk2 == 3);
    //TEST_CHECK(y_pos_walk2 == 6);
}

void testWalkerChaseSoldierdiagonallyDownAndLeftWithObstacleFaceToFace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 8);
    map.add_soldier(&soldier, 2, 8);

    Obstacle osbtacle;
    map.add_obstacle(&osbtacle, 5, 5);

    Walker walker(5,6);
    map.add_zombie(&walker, 5, 6);

    for (int i = 0; i < 40; i++) { // enough to encounter the soldier face to face
        map.chase_soldiers();
    }

    float x_pos_walk = walker.get_x();
    float y_pos_walk = walker.get_y();

    const float epsilon = 0.001;
    double received_numered_x = x_pos_walk;
    double expected_number_x =  2;

    double received_numered_y = y_pos_walk;
    double expected_number_y =  7.8;

    TEST_CHECK(fabs(received_numered_x - expected_number_x) < epsilon);
    TEST_CHECK(fabs(received_numered_y - expected_number_y) < epsilon);
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