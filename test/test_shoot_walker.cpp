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
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1

void testSoldierShootsInfectedSameLineLeft(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 9, 8);
    map.add_soldier(&soldier, 9, 8);

    Infected walker(1,8, map);
    map.add_zombie(&walker, 1, 8);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health < 100);
}

void testSoldierShootsInfectedSameLineRight(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(8,3, map);
    map.add_zombie(&walker, 8, 3);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);

    std::uint16_t remaining_health = walker.get_health();

    TEST_CHECK(remaining_health < 100);
}

void testSoldierShootsInfectedNotSameLineLeft(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 9, 8);
    map.add_soldier(&soldier, 9, 8);

    soldier.move_up();

    Infected walker(1,7, map);
    map.add_zombie(&walker, 1, 7);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_CHECK(remaining_health < 100);
}

void testSoldierShootsOtherSoldierNotSameLineRight(void) {
    GameMap map(10, 10, 0);

    Weapon* idf = new Idf;
    Weapon* idf2 = new Idf;

    Soldier soldier(idf, map, 1, 8);
    map.add_soldier(&soldier, 1, 8);

    Soldier soldier2(idf2, map, 9, 8);
    map.add_soldier(&soldier2, 9, 8);

    soldier2.move_down();

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = soldier2.get_health();
    TEST_CHECK(remaining_health < 100);
}
/*
 * Caso donde el soldado tiene dos zombies para disparar.
 * Siempre dispara primero al zombie que este en el X mas chico.
 * Digamos la "verdadera" posicion
 */
void testSoldierShootsOnly1InfectedOutOf2AimingLeft(){
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 7, 6);
    map.add_soldier(&soldier, 7, 6);

    Infected walker1(3,6, map);
    map.add_zombie(&walker1, 3, 6);

    Infected walker2(2,6, map);
    map.add_zombie(&walker2, 2, 6);

    soldier.set_direction(LEFT);
    soldier.shoot(11);
    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 == 100);
}

void testSoldierShootsAndMissInfectedOutOfRangeLeft(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 9, 8);
    map.add_soldier(&soldier, 9, 8);

    Infected walker(2,7, map);
    map.add_zombie(&walker, 2, 7);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissInfectedOutOfRangeRight(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(5,4, map);
    map.add_zombie(&walker, 5, 4);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingRightTurnedAroundToInfected(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 9, 8);
    map.add_soldier(&soldier, 9, 8);

    Infected walker(1,8, map);
    map.add_zombie(&walker, 1, 8);

    soldier.set_direction(RIGHT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}

void testSoldierShootsAndMissAimingUpTurnedAroundToInfected(void) {
    GameMap map(10, 10, 0);
    Weapon* idf = new Idf;

    Soldier soldier(idf, map, 3, 3);
    map.add_soldier(&soldier, 3, 3);

    Infected walker(8,3, map);
    map.add_zombie(&walker, 8, 3);

    soldier.set_direction(LEFT);
    soldier.shoot(1);
    std::uint16_t remaining_health = walker.get_health();
    TEST_ASSERT(remaining_health == 100);
}


TEST_LIST = {
        {" Soldier shoots walker aiming Left and health decrease", testSoldierShootsInfectedSameLineLeft},
        {" Soldier shoots walker aiming Right and health decrease", testSoldierShootsInfectedSameLineRight},
        {" Soldier shoots walker not same line aiming Left and health decrease", testSoldierShootsInfectedNotSameLineLeft},
        {" Soldier shoots soldier not same line aiming Right and health decrease", testSoldierShootsOtherSoldierNotSameLineRight},
        {" Soldier shoots only 1 walker out of 2 on shooting sight", testSoldierShootsOnly1InfectedOutOf2AimingLeft},
        {" Soldier shoots walker and miss aiming left", testSoldierShootsAndMissInfectedOutOfRangeLeft},
        {" Soldier shoots walker and miss aiming right", testSoldierShootsAndMissInfectedOutOfRangeRight},
        {" Soldier shoots and miss aiming(Right) contrary to walker", testSoldierShootsAndMissAimingRightTurnedAroundToInfected},
        {" Soldier shoots and miss aiming(Left) contrary to walker ",testSoldierShootsAndMissAimingUpTurnedAroundToInfected},
        {NULL, NULL}
};
