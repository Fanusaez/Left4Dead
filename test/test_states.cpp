#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/states/idle.h"
#include "game_logic/weapons/scout.h"

#define UP -1
#define DOWN 1

void testSoldierStartsWithIdleState(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
}

void testSoldierShootsReloadAndStateChangesToReloading(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot();
    soldier.reload(0);

    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}

void testSoldierShootsAndStateChangesToShooting(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(2);

    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}

void testSoldierTryToReloadWithFullMagazineSameState(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.reload(2);

    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(reloading_state == nullptr);
    TEST_ASSERT(old_state != nullptr);
}

void testSoldierShootsWhileReloadingAndStateNotChange(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(); // to be able to reload
    soldier.reload(2);
    soldier.shoot(0.0001); // shoot really fast after reloading

    Shooting* shooting_state = dynamic_cast<Shooting*>(soldier.get_state());
    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(shooting_state == nullptr);
}
/*
 * Esto hay que ver, es un detelle
 * Si termino de recargar y esta en el estado recargando todavia, y recibe la
 * instruccion de disparar, que pase a idle primero o directamente a disparando.
 */
void testSoldierShootsAfterReloadingAndStateChanges(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(); // to be able to reload
    soldier.reload(2);
    soldier.shoot(3);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());
    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(reloading_state == nullptr);
}

void testSoldierUpdatesAfterReloadingAndStateChanges(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(); // to be able to reload
    soldier.reload(2);
    soldier.update(3);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());
    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(reloading_state == nullptr);
}

void testSoldierUpdatesDuringReloadingAndStateChanges(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(); // to be able to reload
    soldier.reload(2);
    soldier.update(2.001);

    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());
    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(idle_state == nullptr);
}

TEST_LIST = {
        {"Soldier start with Idle state", testSoldierStartsWithIdleState},
        {"Soldier shoots and reloads state changes to Reloading", testSoldierShootsReloadAndStateChangesToReloading},
        {"Soldier shoots and state changes to Shooting", testSoldierShootsAndStateChangesToShooting},
        {"Soldier tries to reload with full magazine, state does not change", testSoldierTryToReloadWithFullMagazineSameState},
        {"Soldier tries to shoot while reloading, state not change", testSoldierShootsWhileReloadingAndStateNotChange},
        {"Soldier shoots after finishing the reload and state changes", testSoldierShootsAfterReloadingAndStateChanges},
        {"Soldier updates state after reloading and changes to Idle", testSoldierUpdatesAfterReloadingAndStateChanges},
        {"Soldier updates state during reloading and state still reloading",testSoldierUpdatesDuringReloadingAndStateChanges},
        {NULL, NULL},
};