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

    soldier.shoot();

    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}


TEST_LIST = {
        {"Soldier start with Idle state", testSoldierStartsWithIdleState},
        {"Soldier shoots and reloads state changes to Reloading", testSoldierShootsReloadAndStateChangesToReloading},
        {"Soldier shoots and state changes to Shooting", testSoldierShootsAndStateChangesToShooting},
        {NULL, NULL},
};