#include <cstdint>
#include <iostream>
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
#define SOLDIER_SPEED 0.2
#define ERROR_BOUND 0.0001

void testSoldierStartsWithIdleState(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
}

//****************************************** RELOADING ****************************************************//

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

void testSoldierUpdatesAfterReloadingAndStateChangesToIdle(void) {
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

//****************************************** SHOOTING ****************************************************//

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

void testSoldierShootsAfterReloadingAndStateChangesToShooting(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(); // to be able to reload
    soldier.reload(2);
    soldier.shoot(3);

    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());
    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(reloading_state == nullptr);
}

void testSoldierShootsToFastAndOnlyOneBulletIsFired(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1);
    std::int16_t bullets1 = scout->get_bullets();
    soldier.shoot(1.001);
    std::int16_t bullets2 = scout->get_bullets();

    TEST_ASSERT(bullets1 == bullets2);
}

void testSoldierShootsUntilRunsOutOfAmmoStateChangesToIdle(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    // cada segundo
    for (int i = 0; i < 100; i++){
        soldier.shoot(i);
    }

    std::int16_t bullets1 = scout->get_bullets();
    Shooting* shooting_state = dynamic_cast<Shooting*>(soldier.get_state());
    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(bullets1 == 0);
    TEST_CHECK(shooting_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

//**************************************** MOOVING ********************************************************//

void testSoldierMoveUpAndStateChangesToMoving(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);

    float y_sold = soldier.get_y_position();
    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(fabs(y_sold - 1.8) < ERROR_BOUND);
    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesUpAndImmediatelyReloadStateStaysMoving(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.reload(1.1);

    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesUpAndReload(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);
    soldier.shoot(1); // to be able to reload
    soldier.move_up(2);
    soldier.reload(3); // 1 second later

    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());
    Moving* moving_state = dynamic_cast<Moving*>(soldier.get_state());

    TEST_CHECK(moving_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesUpAndShootsImmediately(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.shoot(1.05);

    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Shooting* shooting_state = dynamic_cast<Shooting*>(soldier.get_state());

    TEST_CHECK(shooting_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldiergetsUpdateAfterMovingChangesToIdle(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.update(2);

    Moving* moving_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(moving_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldiergetsUpdatedImmediatelyAfterMovingChangesToIdle(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.update(1.001);

    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMoveUpTooFastOnlyMoveOnce(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.move_up(1.001);
    soldier.move_up(1.002);

    float y_sold = soldier.get_y_position();
    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(fabs(y_sold - 1.8) < ERROR_BOUND);
    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMoveUpUntilEndOfMap(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 2, 2);
    map.add_soldier(&soldier, 2, 2);

    for (int i = 0; i < 50; i++) {
        soldier.move_up(i); // me muevo cada 1 seg
    }

    float y_sold = soldier.get_y_position();
    std::cout << y_sold;
    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(fabs(y_sold - 0.5) < ERROR_BOUND); // walls limit = 0.5
    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

TEST_LIST = {
        {"Soldier start with Idle state", testSoldierStartsWithIdleState},
        {"Soldier shoots and reloads state changes to Reloading", testSoldierShootsReloadAndStateChangesToReloading},
        {"Soldier shoots and state changes to Shooting", testSoldierShootsAndStateChangesToShooting},
        {"Soldier tries to reload with full magazine, state does not change", testSoldierTryToReloadWithFullMagazineSameState},
        {"Soldier tries to shoot while reloading, state not change", testSoldierShootsWhileReloadingAndStateNotChange},
        {"Soldier shoots after finishing the reload and state changes", testSoldierShootsAfterReloadingAndStateChangesToShooting},
        {"Soldier updates state after reloading and changes to Idle", testSoldierUpdatesAfterReloadingAndStateChangesToIdle},
        {"Soldier updates state during reloading and state still reloading",testSoldierUpdatesDuringReloadingAndStateChanges},
        {"Soldier shoots to fast and only one bullet is fired",testSoldierShootsToFastAndOnlyOneBulletIsFired},
        {"Soldier shoots until runs out of ammo, state changes to Idle", testSoldierShootsUntilRunsOutOfAmmoStateChangesToIdle},
        {"Soldier moves up and state changes to moving", testSoldierMoveUpAndStateChangesToMoving},
        {"Soldier moves up and immediately reloads state not change",testSoldierMovesUpAndImmediatelyReloadStateStaysMoving},
        {"Soldier changes from Moving to Reloading",testSoldierMovesUpAndReload},
        {"Soldier tries to shoot while moving, state not change", testSoldierMovesUpAndShootsImmediately},
        {"Soldier moves and then gets updated, state changes to idle",testSoldiergetsUpdateAfterMovingChangesToIdle},
        {"Soldier gets updated immediately after moving, state still moving", testSoldiergetsUpdatedImmediatelyAfterMovingChangesToIdle},
        {"Soldier moves multiple times but too fast, only moves once",testSoldierMoveUpTooFastOnlyMoveOnce},
       // {"Soldie moves multiple times",testSoldierMoveUpUntilEndOfMap},
        {NULL, NULL},
};