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

void testSoldierShootsWalkerSameLineUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(8,1);
    map.add_zombie(&walker, 8, 1);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsWalkerSameLineDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsWalkerNotSameLineUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(7,1);
    map.add_zombie(&walker, 7, 1);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsWalkerNotSameLineDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 1);
    map.add_soldier(&soldier, 8, 1);

    Walker walker(7,9);
    map.add_zombie(&walker, 7, 9);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}
/*
 * Caso donde el soldado tiene dos zombies para disparar.
 * Siempre dispara primero al zombie que este en el X mas chico.
 * Digamos la "verdadera" posicion
 */
void testSoldierShootsOnly1WalkerOutOf2AimingUp(){
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 7, 7);
    map.add_soldier(&soldier, 7, 7);

    Walker walker1(6,3);
    map.add_zombie(&walker1, 6, 3);

    Walker walker2(8,3);
    map.add_zombie(&walker2, 8, 3);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 == 100);
}

void testSoldierShootsAndMissWalkerOutOfRangeUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(6,1);
    map.add_zombie(&walker, 6, 1);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissWalkerOutOfRangeDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(5,8);
    map.add_zombie(&walker, 5, 8);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingDownTurnedAroundToWalker(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(8,1);
    map.add_zombie(&walker, 8, 1);

    soldier.set_direction(DOWN);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingUpTurnedAroundToWalker(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    soldier.set_direction(UP);
    soldier.shoot();
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}


TEST_LIST = {
        {" Soldier shoots walker aiming Left and health decrease", testSoldierShootsWalkerSameLineUp},
        {" Soldier shoots walker aiming Right and health decrease", testSoldierShootsWalkerSameLineDown},
        {" Soldier shoots walker not same line aiming Left and health decrease", testSoldierShootsWalkerNotSameLineUp},
        {" Soldier shoots walker not same line aiming Right and health decrease", testSoldierShootsWalkerNotSameLineDown},
        {" Soldier shoots only 1 walker out of 2 on shooting sight", testSoldierShootsOnly1WalkerOutOf2AimingUp},
        {" Soldier shoots walker and miss aiming left", testSoldierShootsAndMissWalkerOutOfRangeUp},
        {" Soldier shoots walker and miss aiming right", testSoldierShootsAndMissWalkerOutOfRangeDown},
        {" Soldier shoots and miss aiming(down) contrary to walker", testSoldierShootsAndMissAimingDownTurnedAroundToWalker},
        {" Soldier shoots and miss aiming(up) contrary to walker ",testSoldierShootsAndMissAimingUpTurnedAroundToWalker},
        {NULL, NULL}
};
