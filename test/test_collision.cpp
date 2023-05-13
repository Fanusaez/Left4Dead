#include <cstdint>
#include "acutest.h"
#include "../src/soldier.h"
#include "../src/walker.h"
#include "../src/map.h"
#include "../src/game_object.h"
#include "../src/idf.h"
#include "../src/weapon.h"

void testCollisionSameLineUp(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 9, 9);
    map.add_zombie(&walker, 9, 1);
    TEST_ASSERT(map.collision(-1, 9, 8) == true);
    delete soldier;
}

void testCollisionSameLineDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 7, 0);
    map.add_zombie(&walker, 7, 5);
    TEST_ASSERT(map.collision(1, 7, 1) == true);
    delete soldier;
     }

void testNoCollisionSameLineUp(void) {
   Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 9, 9);
    map.add_zombie(&walker, 1, 1);
    TEST_ASSERT(map.collision(-1, 9, 8) == false);
    delete soldier;
}

void testNoCollisionSameLineDown(void) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf);
    Walker walker;
    GameMap map(10, 10);
    map.add_soldier(soldier, 5, 5);
    map.add_zombie(&walker, 8, 8);
    TEST_ASSERT(map.collision(1, 5, 6) == false);
    delete soldier;
}

TEST_LIST = {
        {"Testing collision going up", testCollisionSameLineUp},
        {"Testing collision going down", testCollisionSameLineDown},
        {"Testing No collision going up", testNoCollisionSameLineUp},
        {"Testing No collision going down", testNoCollisionSameLineDown},
        {NULL, NULL}
};