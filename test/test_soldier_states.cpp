#include <cstdint>
#include <iostream>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/p90.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/states/idle.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/states/throwing_explosive_grenade.h"
#include "game_logic/states/calling_air_strike.h"
#include "game_logic/states/throwing_smoke_grenade.h"
#include "game_logic/states/dead.h"
#include "game_logic/states/being_attacked.h"
#include "game_logic/states/reloading.h"
#include "game_logic/states/moving.h"
#include "game_logic/states/shooting.h"

#define UP -1
#define DOWN 1
#define DAMAGE_GRENADE 40

void testSoldierStartsWithIdleState(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
}

//****************************************** RELOADING ****************************************************//

void testSoldierShootsReloadAndStateChangesToReloading(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1);
    soldier.reload(0);

    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}

void testSoldierTryToReloadWithFullMagazineSameState(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.reload(2);

    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(reloading_state == nullptr);
    TEST_ASSERT(old_state != nullptr);
}

void testSoldierShootsWhileReloadingAndStateNotChange(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1); // to be able to reload
    soldier.reload(2);
    soldier.shoot(2.0001); // shoot really fast after reloading

    Shooting* shooting_state = dynamic_cast<Shooting*>(soldier.get_state());
    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(shooting_state == nullptr);
}

void testSoldierUpdatesAfterReloadingAndStateChangesToIdle(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1); // to be able to reload
    soldier.reload(2);
    soldier.update(3);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());
    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(reloading_state == nullptr);
}

void testSoldierUpdatesDuringReloadingAndStateChanges(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1); // to be able to reload
    soldier.reload(2);
    soldier.update(2.001);

    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());
    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(idle_state == nullptr);
}

//****************************************** SHOOTING ****************************************************//

void testSoldierShootsAndStateChangesToShooting(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(2);

    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());
    Idle* old_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}

void testSoldierShootsAfterReloadingAndStateChangesToShooting(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1); // to be able to reload
    soldier.reload(2);
    soldier.shoot(3);

    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());
    Reloading* reloading_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_ASSERT(soldier_state != nullptr);
    TEST_ASSERT(reloading_state == nullptr);
}

void testSoldierShootsToFastAndOnlyOneBulletIsFired(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    soldier.shoot(1);
    std::int16_t bullets1 = scout->get_bullets();
    soldier.shoot(1.001);
    std::int16_t bullets2 = scout->get_bullets();

    TEST_ASSERT(bullets1 == bullets2);
}

void testSoldierShootsUntilRunsOutOfAmmoStateChangesToIdle(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
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
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);

    float y_sold = soldier.get_y_pos();
    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesUpAndImmediatelyReload(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);
    soldier.shoot(1);
    soldier.move_up(2);
    soldier.reload(2.001);

    Moving* moving_state = dynamic_cast<Moving*>(soldier.get_state());
    Reloading* soldier_state = dynamic_cast<Reloading*>(soldier.get_state());

    TEST_CHECK(moving_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesUpAndReload(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
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
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.shoot(1.05);

    Moving* moving_state = dynamic_cast<Moving*>(soldier.get_state());
    Shooting* soldier_state = dynamic_cast<Shooting*>(soldier.get_state());

    TEST_CHECK(moving_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMovesAndThenItsToldToStopChangesToIdle(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.stop_action();

    Moving* moving_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(moving_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldiergetsUpdatedImmediatelyAfterMovingChangesToIdle(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.update(1.001);

    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMoveUpTooFastOnlyMoveOnce(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.move_up(1);
    soldier.move_up(1.001);
    soldier.move_up(1.002);

    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierMoveUpUntilEndOfMap(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    for (int i = 0; i < 50; i++) {
        soldier.move_up(i); // me muevo cada 1 seg
    }

    float y_sold = soldier.get_y_pos();
    Moving* soldier_state = dynamic_cast<Moving*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

//**************************************** BEING ATTACKED *************************************************//

void testSoldierStartsIdleAndIsAttacked(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    map.attack_soldiers(1);
    map.attack_soldiers(2);

    BeingAttacked* soldier_state = dynamic_cast<BeingAttacked*>(soldier.get_state());
    Idle* idle_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(idle_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierShootingAndIsAttacked(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    soldier.shoot(0);

    map.attack_soldiers(1);
    map.attack_soldiers(2);

    BeingAttacked* soldier_state = dynamic_cast<BeingAttacked*>(soldier.get_state());
    Shooting* shooting_state = dynamic_cast<Shooting*>(soldier.get_state());

    TEST_CHECK(shooting_state == nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierReloadingAndIsAttacked(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    soldier.shoot(0);
    soldier.reload(1);

    Reloading* rel_state = dynamic_cast<Reloading*>(soldier.get_state());

    map.attack_soldiers(1);
    map.attack_soldiers(2);

    BeingAttacked* soldier_state = dynamic_cast<BeingAttacked*>(soldier.get_state());


    TEST_CHECK(rel_state != nullptr);
    TEST_CHECK(soldier_state != nullptr);
}

//************************************************ DEAD *******************************************//

void testSoldierGetsKilledAndStateChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    for (int i = 0; i < 15; i++) {
        map.attack_soldiers(i);
    }

    Dead* soldier_state = dynamic_cast<Dead*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierGetsKilledAndTryToMove(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    for (int i = 0; i < 15; i++) {
        map.attack_soldiers(i);
    }
    soldier.move_up(20);

    Dead* soldier_state = dynamic_cast<Dead*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierGetsKilledAndTryToShoot(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    for (int i = 0; i < 15; i++) {
        map.attack_soldiers(i);
    }
    soldier.shoot(20);

    Dead* soldier_state = dynamic_cast<Dead*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierGetsKilledAndTryToReload(void) {
    GameMap map(10, 10, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    Infected walker(2, 3, 0, map);
    map.add_zombie(&walker, 2, 3);

    for (int i = 0; i < 15; i++) {
        map.attack_soldiers(i);
    }
    soldier.reload(20);

    Dead* soldier_state = dynamic_cast<Dead*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

// *************************************** THROWING GRENADE ********************************//

void testSoldierThrowsGrenadeAndStateChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *idf = new Idf(0, 0);

    Soldier soldier(idf, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_explosive_grenade(100);

    ThrowingExplosiveGrenade* soldier_state = dynamic_cast<ThrowingExplosiveGrenade*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierThrowsGrenadeAndTenSecondsPasses(void) {
    GameMap map(10, 10, 0);
    Weapon *idf = new Idf(0, 0);

    Soldier soldier(idf, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_explosive_grenade(100);
    soldier.update(110);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierThrows2GrenadeOnly1IsThrown(void) {
    GameMap map(10, 10, 0);
    Weapon *idf = new Scout(0, 0);

    Soldier soldier(idf, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);
    soldier.set_direction(DOWN);

    Infected walker(6, 2, 0, map);
    map.add_zombie(&walker, 6, 2);

    soldier.throw_explosive_grenade(100);
    soldier.throw_explosive_grenade(101);
    soldier.update(200);

    std::int16_t walker_health = walker.get_health();
    TEST_CHECK(walker_health == 100 - DAMAGE_GRENADE);
}

void testSoldierThrowsGrenadeWithP90AndStateNotChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *p90 = new P90(0);

    Soldier soldier(p90, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_explosive_grenade(100);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

// *************************************** THROWING SMOKE GRENADE ********************************//

void testSoldierThrowsSmokeGrenadeAndStateChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *idf = new Idf(0, 0);

    Soldier soldier(idf, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_smoke_grenade(100);

    ThrowingSmokeGrenade* soldier_state = dynamic_cast<ThrowingSmokeGrenade*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierThrowsSmokeGrenadeAndTenSecondsPasses(void) {
    GameMap map(10, 10, 0);
    Weapon *idf = new Idf(0, 0);

    Soldier soldier(idf, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_explosive_grenade(100);
    soldier.update(110);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

void testSoldierThrowsSmokeGrenadeWithP90AndStateNotChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *p90 = new P90(0);

    Soldier soldier(p90, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.throw_smoke_grenade(100);

    Idle* soldier_state = dynamic_cast<Idle*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}

// ******************************************* CALLING AIR STRIKE *****************************************************//

void testSoldierCallsAirStrikeWithP90AndStateChanges(void) {
    GameMap map(10, 10, 0);
    Weapon *p90 = new P90(0);

    Soldier soldier(p90, map, 2, 2, 0);
    map.add_soldier(&soldier, 2, 2);

    soldier.call_air_strike(100);

    CallingAirStrike* soldier_state = dynamic_cast<CallingAirStrike*>(soldier.get_state());

    TEST_CHECK(soldier_state != nullptr);
}



TEST_LIST = {
        {"Soldier start with Idle state",                                     testSoldierStartsWithIdleState},
        {"Soldier shoots and reloads state changes to Reloading",             testSoldierShootsReloadAndStateChangesToReloading},
        {"Soldier shoots and state changes to Shooting",                      testSoldierShootsAndStateChangesToShooting},
        {"Soldier tries to reload with full magazine, state does not change", testSoldierTryToReloadWithFullMagazineSameState},
        {"Soldier tries to shoot while reloading, state not change",          testSoldierShootsWhileReloadingAndStateNotChange},
        {"Soldier shoots after finishing the reload and state changes",       testSoldierShootsAfterReloadingAndStateChangesToShooting},
        {"Soldier updates state after reloading and changes to Idle",         testSoldierUpdatesAfterReloadingAndStateChangesToIdle},
        {"Soldier updates state during reloading and state still reloading",  testSoldierUpdatesDuringReloadingAndStateChanges},
        {"Soldier shoots to fast and only one bullet is fired",               testSoldierShootsToFastAndOnlyOneBulletIsFired},
        {"Soldier shoots until runs out of ammo, state changes to Idle",      testSoldierShootsUntilRunsOutOfAmmoStateChangesToIdle},
        {"Soldier moves up and state changes to moving",                      testSoldierMoveUpAndStateChangesToMoving},
        {"Soldier moves up and immediately reloads state not change",         testSoldierMovesUpAndImmediatelyReload},
        {"Soldier changes from Moving to Reloading",                          testSoldierMovesUpAndReload},
        {"Soldier tries to shoot while moving, state not change",             testSoldierMovesUpAndShootsImmediately},
        {"Soldier moves and then gets updated, state changes to idle",        testSoldierMovesAndThenItsToldToStopChangesToIdle},
        {"Soldier gets updated immediately after moving, state still moving", testSoldiergetsUpdatedImmediatelyAfterMovingChangesToIdle},
        {"Soldier moves multiple times but too fast, only moves once",        testSoldierMoveUpTooFastOnlyMoveOnce},
        {"Soldier moves multiple times",                                      testSoldierMoveUpUntilEndOfMap},
        {"Soldier is in state idle and is attacked, state changes",           testSoldierStartsIdleAndIsAttacked},
        {"Soldier is in state Shooting and is attacked, state changes",       testSoldierShootingAndIsAttacked},
        {"Soldier is in state Reloading and is attacked, state changes",      testSoldierReloadingAndIsAttacked},
        {"Soldier gets killed and state changes",                             testSoldierGetsKilledAndStateChanges},
        {"Soldier gets killed and tries to move", testSoldierGetsKilledAndTryToMove},
        {"Soldier gets killed and tries to reload", testSoldierGetsKilledAndTryToReload},
        {"Soldier gets killed and tries to shoot", testSoldierGetsKilledAndTryToShoot},
        {"Soldier throws grenade and state changes to Throwing...",testSoldierThrowsGrenadeAndStateChanges},
        {"Soldier throws grenade time passes and state change to idle", testSoldierThrowsGrenadeAndTenSecondsPasses},
        {"Soldier tries to throw 2 grenade, only 1 succeed", testSoldierThrows2GrenadeOnly1IsThrown},
        {"Soldier tries throwing grenade with p90, not happening", testSoldierThrowsGrenadeWithP90AndStateNotChanges},
        {"Soldier throws smoke grenade and state changes to Throwing...",testSoldierThrowsSmokeGrenadeAndStateChanges},
        {"Soldier throws smoke grenade time passes and state change to idle", testSoldierThrowsSmokeGrenadeAndTenSecondsPasses},
        {"Soldier tries throwing smoke grenade with p90, not happening", testSoldierThrowsSmokeGrenadeWithP90AndStateNotChanges},
        {"Soldier calls for an air strike and state changes",testSoldierCallsAirStrikeWithP90AndStateChanges},
        {NULL, NULL},
};