#include <cstdint>
#include <iostream>
#include "../acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/states/idle.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/zombies/witch.h"

#define UP -1
#define DOWN 1

void testInfectedStartsWithIdleState(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    ZombieIdle* walker_state = dynamic_cast<ZombieIdle*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
     map.empty_vectors();
}

//****************************************** Moving ****************************************************//

void testInfectedChaseAndStateChangesToWalking(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);

    Walking* walker_state = dynamic_cast<Walking*>(walker.get_state());
    ZombieIdle* old_state = dynamic_cast<ZombieIdle*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
     map.empty_vectors();
}
void testInfectedChaseTwiceTooFastAndmoves1Time(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);
    float x_pos1 = walker.get_x_pos();
    float y_pos1 = walker.get_y_pos();

    map.chase_soldiers(1.01);
    float x_pos2 = walker.get_x_pos();
    float y_pos2 = walker.get_y_pos();

    TEST_ASSERT(x_pos1 == x_pos2);
    TEST_ASSERT(y_pos1 == y_pos2);
     map.empty_vectors();
}

void testInfectedChaseTwiceAndmoves2Times(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 8, 9, 0);
    map.add_soldier(&soldier, 8, 9);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);
    std::int16_t y_pos1 = walker.get_y_pos();

    map.chase_soldiers(3);
    std::int16_t y_pos2 = walker.get_y_pos();

    TEST_CHECK(y_pos1 != y_pos2);
     map.empty_vectors();
}

//*********************************************** ATTACKING *************************************************//

void testInfectedAttacksSoldierAndStateChangesToAttackingButDoesNotHurtTheSoldierYet(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 6, 0);
    map.add_soldier(&soldier, 5, 6);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);

    ZombieIdle* idle_state = dynamic_cast<ZombieIdle*>(walker.get_state());
    Attacking* walker_state = dynamic_cast<Attacking*>(walker.get_state());

    std::int16_t health = soldier.get_health();

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(idle_state == nullptr);
    TEST_CHECK(health == 100);
     map.empty_vectors();
}

void testInfectedAttacks2TimesToFastOnlyAttacksOnce(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 6, 0);
    map.add_soldier(&soldier, 5, 6);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);
    std::int16_t health = soldier.get_health();
    map.attack_soldiers(1.01);
    std::int16_t health2 = soldier.get_health();

    TEST_CHECK(health == health2);
     map.empty_vectors();
}

void testInfectedAttacks2Times(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 5, 6, 0);
    map.add_soldier(&soldier, 5, 6);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);
    std::int16_t health = soldier.get_health();
    map.attack_soldiers(2);
    std::int16_t health2 = soldier.get_health();

    TEST_CHECK(health != health2);
     map.empty_vectors();
}

//************************************************** BEING ATTACKED *****************************************//


void testInfectedGetsAttacked(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 6, 5, 0);
    map.add_soldier(&soldier, 6, 5);
    soldier.set_direction(LEFT);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);

    soldier.shoot(1);

    ZombieIdle* idle_state = dynamic_cast<ZombieIdle*>(walker.get_state());
    ZombieBeingAttacked* walker_state = dynamic_cast<ZombieBeingAttacked*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(idle_state == nullptr);
    TEST_CHECK(walker.get_health() < 100);
     map.empty_vectors();
}

void testInfectedWalkingAndGetsAttacked(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 6, 5, 0);
    map.add_soldier(&soldier, 6, 5);
    soldier.set_direction(LEFT);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);
    map.chase_soldiers(1);

    Walking* old_state = dynamic_cast<Walking*>(walker.get_state());

    soldier.shoot(1);

    ZombieBeingAttacked* walker_state = dynamic_cast<ZombieBeingAttacked*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(old_state != nullptr);
    TEST_CHECK(walker.get_health() < 100);
     map.empty_vectors();
}

void testInfectedgetsShotAndDie(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 6, 5, 0);
    map.add_soldier(&soldier, 6, 5);
    soldier.set_direction(LEFT);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);
    map.chase_soldiers(1);

    Walking* old_state = dynamic_cast<Walking*>(walker.get_state());

    for (int i = 0; i < 10; i++) {
        soldier.shoot(i);
    }

    ZombieDead* walker_state = dynamic_cast<ZombieDead*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(old_state != nullptr);
    TEST_CHECK(walker.get_health() < 100);
     map.empty_vectors();
}

void testInfectedgetsShotWhileAttacking(void) {
    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier(scout, map, 4, 5, 0);
    map.add_soldier(&soldier, 4, 5);
    soldier.set_direction(LEFT);

    Soldier soldier2(scout2, map, 6, 5, 0);
    map.add_soldier(&soldier2, 6, 5);
    soldier2.set_direction(LEFT);

    Infected walker(5, 5, 0, map);
    map.add_zombie(&walker, 5, 5);
    map.attack_soldiers(1);

    Attacking* old_state = dynamic_cast<Attacking*>(walker.get_state());

    soldier.shoot(2);
    soldier2.shoot(2);

    ZombieBeingAttacked* walker_state = dynamic_cast<ZombieBeingAttacked*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(old_state != nullptr);
    TEST_CHECK(walker.get_health() < 100);
     map.empty_vectors();
}

//********************************************** STUNNED *****************************************************//

void testSoldierThrowsSmokeGrenadeAndStunnedZombie(void) {

    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 9, 5, 0);
    map.add_soldier(&soldier, 9, 5);

    soldier.set_direction(LEFT);

    Infected walker1(5 , 5, 0, map); // donde cae la granada
    map.add_zombie(&walker1, 5,5);

    soldier.throw_smoke_grenade(100);
    soldier.update(200);

    Stunned* zombie_state1 = dynamic_cast<Stunned*>(walker1.get_state());

    TEST_CHECK(zombie_state1 != nullptr);
     map.empty_vectors();
}

//************************************** SCREAM *****************************************************8//

void testWitcherScreamsStatesChanges(void) {

    GameMap map(10, 10, 0);
    Weapon* scout = new Scout(0, 0);

    Witch witch(5, 5,0, map); // donde cae la granada
    map.add_zombie(&witch, 5,5);

    witch.scream(1);

    Screaming* zombie_state = dynamic_cast<Screaming*>(witch.get_state());

    TEST_CHECK(zombie_state != nullptr);
     map.empty_vectors();
}

TEST_LIST = {
        {"Infected start with Idle state", testInfectedStartsWithIdleState},
        {"Infected shoots and reloads state changes to Reloading", testInfectedChaseAndStateChangesToWalking},
        {"Infected gets called 2 times chase but too fast", testInfectedChaseTwiceTooFastAndmoves1Time},
        {"Infected gets called 2 times chase and moves 2 times",testInfectedChaseTwiceAndmoves2Times},
        //{"Infected attacks and state change to Attacking", testInfectedAttacksSoldierAndStateChangesToAttackingButDoesNotHurtTheSoldierYet},
        {"Infected attacks 2 times fast, only attacks once",testInfectedAttacks2TimesToFastOnlyAttacksOnce},
        {"Infected attacks twice",testInfectedAttacks2Times},
        {"Infected gets attacked, state changes and health decrease",testInfectedGetsAttacked},
        {"Infected gets attacked while walking",testInfectedWalkingAndGetsAttacked},
        {"Infected gets killed", testInfectedgetsShotAndDie},
        {"Infected gets shot while attacking",testInfectedgetsShotWhileAttacking},
        {"Zombie gets stunned",testSoldierThrowsSmokeGrenadeAndStunnedZombie},
        {"Witcher screams and state changes",testWitcherScreamsStatesChanges},
        {NULL, NULL},
};
