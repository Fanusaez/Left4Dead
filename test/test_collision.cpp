#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/idf.h"
#include "game_logic/weapon.h"

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define UP -1
#define DOWN 1

/*
 * Colisiones:
 * Todos los objetos del juego (por ahora walkers y soldados) utilizan dos espacios en X y uno en Y.
 * La posicion que se indiaca en X en los test es la de la izquierda.
 * Por ejemplo: si agrego un soldado en la posicion (1,3), este soldado verdaderamente ocupara en la matriz
 * la posicion x_pos = [1,2] y_pos = 3.
 */


void testCollisionSameLineUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    GameObject* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 8, 9);

    Walker walker(8, 1);
    map.add_zombie(&walker, 8, 1);

    TEST_ASSERT(map.collision(UP, 8, 8) == true);
    delete soldier;
}

void testCollisionSameLineDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 7, 0);

    Walker walker(7, 5);
    map.add_zombie(&walker, 7, 5);

    TEST_ASSERT(map.collision(DOWN, 7, 1) == true);
    delete soldier;
}

void testCollisionNotSameLineLeftUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 8, 9);

    Walker walker(7, 1);
    map.add_zombie(&walker, 7, 1);

    TEST_ASSERT(map.collision(UP, 8, 8) == true);
    delete soldier;
}

void testCollisionNotSameLineRightUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 7, 9);

    Walker walker(8, 1);
    map.add_zombie(&walker, 8, 1);

    TEST_ASSERT(map.collision(UP, 7, 8) == true);
    delete soldier;
}

void testCollisionNotSameLineLeftDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 1, 1);

    Walker walker(0, 9);
    map.add_zombie(&walker, 0, 9);

    TEST_ASSERT(map.collision(DOWN, 1, 2) == true);
    delete soldier;
}

void testCollisionNotSameLineRightDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 1, 1);

    Walker walker(2, 9);
    map.add_zombie(&walker, 2, 9);

    TEST_ASSERT(map.collision(DOWN, 1, 2) == true);
    delete soldier;
}

void testNoCollisionUp(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 8, 9);

    Walker walker(1,1);
    map.add_zombie(&walker, 1, 1);

    TEST_ASSERT(map.collision(UP, 8, 8) == false);
    delete soldier;
}

void testNoCollisionDown(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* idf = new Idf;

    Soldier* soldier = new Soldier(idf, map);
    map.add_soldier(soldier, 1, 1);

    Walker walker(8, 9);
    map.add_zombie(&walker, 8, 9);

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