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

void testWalkerStartsWithIdleState(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    ZombieIdle* walker_state = dynamic_cast<ZombieIdle*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
}

//****************************************** Moving ****************************************************//

void testWalkerChaseAndStateChangesToWalking(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);

    Walking* walker_state = dynamic_cast<Walking*>(walker.get_state());
    ZombieIdle* old_state = dynamic_cast<ZombieIdle*>(walker.get_state());

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(old_state == nullptr);
}
void testWalkerChaseTwiceTooFastAndmoves1Time(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);
    float x_pos1 = walker.get_x();
    float y_pos1 = walker.get_y();

    map.chase_soldiers(1.01);
    float x_pos2 = walker.get_x();
    float y_pos2 = walker.get_y();

    TEST_ASSERT(x_pos1 == x_pos2);
    TEST_ASSERT(y_pos1 == y_pos2);
}

void testWalkerChaseTwiceAndmoves2Times(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 8, 9);
    map.add_soldier(&soldier, 8, 9);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.chase_soldiers(1);
    float x_pos1 = walker.get_x();

    map.chase_soldiers(3);
    float x_pos2 = walker.get_x();

    TEST_CHECK(x_pos1 != x_pos2);
}

//*********************************************** ATTACKING *************************************************//

void testWalkerAttacksSoldierAndStateChangesToAttacking(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 6);
    map.add_soldier(&soldier, 5, 6);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);

    ZombieIdle* idle_state = dynamic_cast<ZombieIdle*>(walker.get_state());
    Attacking* walker_state = dynamic_cast<Attacking*>(walker.get_state());

    std::int16_t health = soldier.get_health();

    TEST_ASSERT(walker_state != nullptr);
    TEST_ASSERT(idle_state == nullptr);
    TEST_CHECK(health < 100);
}

void testWalkerAttacks2TimesToFastOnlyAttacksOnce(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 6);
    map.add_soldier(&soldier, 5, 6);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);
    std::int16_t health = soldier.get_health();
    map.attack_soldiers(1.01);
    std::int16_t health2 = soldier.get_health();

    TEST_CHECK(health == health2);
}

void testWalkerAttacks2Times(void) {
    GameMap map(10, 10);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 5, 6);
    map.add_soldier(&soldier, 5, 6);

    Walker walker(5,5);
    map.add_zombie(&walker, 5, 5);

    map.attack_soldiers(1);
    std::int16_t health = soldier.get_health();
    map.attack_soldiers(2);
    std::int16_t health2 = soldier.get_health();

    TEST_CHECK(health != health2);
}


TEST_LIST = {
        {"Walker start with Idle state", testWalkerStartsWithIdleState},
        {"Walker shoots and reloads state changes to Reloading", testWalkerChaseAndStateChangesToWalking},
        {"Walker gets called 2 times chase but too fast", testWalkerChaseTwiceTooFastAndmoves1Time},
        {"Walker gets called 2 times chase and moves 2 times",testWalkerChaseTwiceAndmoves2Times},
        {"Walker attacks and state change to Attacking", testWalkerAttacksSoldierAndStateChangesToAttacking},
        {"Walker attacks 2 times fast, only attacks once",testWalkerAttacks2TimesToFastOnlyAttacksOnce},
        {"Walke attacks twice",testWalkerAttacks2Times},
        {NULL, NULL},
};
