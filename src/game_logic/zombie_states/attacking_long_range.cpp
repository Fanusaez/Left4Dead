#include "attacking_long_range.h"
#include "../soldier.h"
#include "zombie_idle.h"
#include "attacking.h"
#include "running.h"
#include "jumping.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"
#include "screaming.h"


AttackingLongRange::AttackingLongRange(Soldier* closest_soldier, std::int16_t damage, float time)  :
        start_time(time),
        waiting_time_to_attack(CONFIGURATION.get_zombieState_attacking_time())
{
    zombie_state = ATTACKING_VENOM_LONG_RANGE;
    closest_soldier->receive_damage(damage, time);
}

ZombieState *AttackingLongRange::update(float time) {
    if (time_to_attack(time)) {
        return new ZombieIdle;
    }
    return nullptr;
}

ZombieState *
AttackingLongRange::chase_soldier(Chaser& chaser,
                         std::int16_t x_pos_chase,
                         std::int16_t y_pos_chase,
                         float time) {
    if (time_to_attack(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
AttackingLongRange::chase_soldier_running(Chaser& chaser,
                                 std::int16_t x_pos_chase,
                                 std::int16_t y_pos_chase,
                                 float time) {
    if (time_to_attack(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
AttackingLongRange::chase_soldier_jumping(Chaser& chaser,
                                 Soldier* soldier,
                                 std::int16_t damage,
                                 std::int16_t x_pos_chase,
                                 std::int16_t y_pos_chase,
                                 float time) {
    if (time_to_attack(time)) {
        return new Jumping(chaser, soldier, damage, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *AttackingLongRange::attack_soldier(Soldier* closest_soldier,
                                       std::int16_t damage,
                                       float time) {
    if (time_to_attack(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *AttackingLongRange::attack_soldier_long_range(Soldier *closest_soldier,
                                                           std::int16_t damage,
                                                           float time) {
    if (time_to_attack(time)) {
        start_time = time;
        closest_soldier->receive_damage(damage, time);
    }
    return nullptr;
}


ZombieState* AttackingLongRange::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState *AttackingLongRange::die(float time) {
    return new ZombieDead(time);
}

ZombieState *AttackingLongRange::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *AttackingLongRange::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

bool AttackingLongRange::time_to_attack(float time) {
    return (time - start_time) >= waiting_time_to_attack;
}

void AttackingLongRange::set_speed(float speed) {
    waiting_time_to_attack = speed;
}

