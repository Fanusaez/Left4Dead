#include <cstdint>
#include "acutest.h"
#include "../src/soldier.h"
#include "../src/walker.h"
#include "../src/map.h"
#include "../src/game_object.h"
#include "../src/idf.h"
#include "../src/weapon.h"
#define UP -1
#define DOWN 1

void testCollisionSameLineUp(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 8, 9);
    map.add_zombie(&walker, 8, 1);
    TEST_ASSERT(map.collision(UP, 8, 8) == true);
    delete soldier;
}

void testCollisionSameLineDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 7, 0);
    map.add_zombie(&walker, 7, 5);
    TEST_ASSERT(map.collision(DOWN, 7, 1) == true);
    delete soldier;
}

void testCollisionNotSameLineLeftUp(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 8, 9);
    map.add_zombie(&walker, 7, 1);
    TEST_ASSERT(map.collision(UP, 8, 8) == true);
    delete soldier;
}

void testCollisionNotSameLineRightUp(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 8, 9);
    map.add_zombie(&walker, 9, 1);
    TEST_ASSERT(map.collision(UP, 8, 8) == true);
    delete soldier;
}

void testCollisionNotSameLineLeftDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 1, 1);
    map.add_zombie(&walker, 0, 9);
    TEST_ASSERT(map.collision(DOWN, 1, 2) == true);
    delete soldier;
}

void testCollisionNotSameLineRightDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 1, 1);
    map.add_zombie(&walker, 2, 9);
    TEST_ASSERT(map.collision(DOWN, 1, 2) == true);
    delete soldier;
}

void testNoCollisionUp(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 9, 9);
    map.add_zombie(&walker, 1, 1);
    TEST_ASSERT(map.collision(UP, 9, 8) == false);
    delete soldier;
}

void testNoCollisionDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 1, 1);
    map.add_zombie(&walker, 9, 9);
    TEST_ASSERT(map.collision(DOWN, 5, 2) == false);
    delete soldier;
}

TEST_LIST = {
        {"Testing collision going up", testCollisionSameLineUp},
        {"Testing collision going down", testCollisionSameLineDown},
        {"Testing collision going up not same line left", testCollisionNotSameLineLeftUp},
        {"Testing collision going up not same line right",testCollisionNotSameLineRightUp},
        {"Testing collision going down not same line left",testCollisionNotSameLineLeftDown},
        {"Testing collision going down not same line right",testCollisionNotSameLineRightDown},
        {"Testing No collision going up", testNoCollisionUp},
        {"Testing No collision going down", testNoCollisionDown},
        {NULL, NULL}
};