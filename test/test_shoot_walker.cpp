#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#define UP -1
#define DOWN 1
#define MOVEMENTS_PER_CELL 15
#define MOV_NEEDED_TO_WALK_ALL_CELL 14

void testSoldierShootsInfectedSameLineUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(8,1, map);
    map.add_zombie(&walker, 8, 1);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsInfectedSameLineDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(3,8, map);
    map.add_zombie(&walker, 3, 8);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsInfectedNotSameLineUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(7,1, map);
    map.add_zombie(&walker, 7, 1);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}

void testSoldierShootsInfectedNotSameLineDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 1);
    map.add_soldier(&soldier, 8, 1);

    Infected walker(7,9, map);
    map.add_zombie(&walker, 7, 9);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health < 100);
}
/*
 * Caso donde el soldado tiene dos zombies para disparar.
 * Siempre dispara primero al zombie que este en el X mas chico.
 * Digamos la "verdadera" posicion
 */
void testSoldierShootsOnly1InfectedOutOf2AimingUp(){
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 7, 7);
    map.add_soldier(&soldier, 7, 7);

    Infected walker1(6,3, map);
    map.add_zombie(&walker1, 6, 3);

    Infected walker2(8,3, map);
    map.add_zombie(&walker2, 8, 3);

    soldier.set_direction(UP);
    soldier.shoot(11);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 == 100);
}

void testSoldierShootsAndMissInfectedOutOfRangeUp(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(6,1, map);
    map.add_zombie(&walker, 6, 1);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissInfectedOutOfRangeDown(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(5,8, map);
    map.add_zombie(&walker, 5, 8);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingDownTurnedAroundToInfected(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(8,1, map);
    map.add_zombie(&walker, 8, 1);

    soldier.set_direction(DOWN);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingUpTurnedAroundToInfected(void) {
    GameMap map(10, 10);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(3,8, map);
    map.add_zombie(&walker, 3, 8);

    soldier.set_direction(UP);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}


TEST_LIST = {
        {" Soldier shoots walker aiming Left and health decrease", testSoldierShootsInfectedSameLineUp},
        {" Soldier shoots walker aiming Right and health decrease", testSoldierShootsInfectedSameLineDown},
        {" Soldier shoots walker not same line aiming Left and health decrease", testSoldierShootsInfectedNotSameLineUp},
        {" Soldier shoots walker not same line aiming Right and health decrease", testSoldierShootsInfectedNotSameLineDown},
        {" Soldier shoots only 1 walker out of 2 on shooting sight", testSoldierShootsOnly1InfectedOutOf2AimingUp},
        {" Soldier shoots walker and miss aiming left", testSoldierShootsAndMissInfectedOutOfRangeUp},
        {" Soldier shoots walker and miss aiming right", testSoldierShootsAndMissInfectedOutOfRangeDown},
        {" Soldier shoots and miss aiming(down) contrary to walker", testSoldierShootsAndMissAimingDownTurnedAroundToInfected},
        {" Soldier shoots and miss aiming(up) contrary to walker ",testSoldierShootsAndMissAimingUpTurnedAroundToInfected},
        {NULL, NULL}
};
